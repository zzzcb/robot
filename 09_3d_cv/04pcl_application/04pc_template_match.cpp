//
// Created by zcb on 6/14/21.
//
/*
 * 点云模板匹配
 * 目标点云 person.pcd
 * 模板点云 (多个) object_template_0-5.pcd
 * 循环多个模板,找出评分最高的模板,后面输出 该模板 变换到目标点云中对应位置的 R和t
 * http://robot.czxy.com/docs/pcl/chapter04/template_alignment/
 */
/*
 * 注: 已知模板在相机下的位姿
 *
 * 输入: 模板点云文件(一个或多个) 和 目标点云
 *
 * 输出: 模板 变换到 目标点云中相应点云 的变换矩阵
 *
 * 用法: ./out ../data/object_templates.txt ../data/person.pcd
 *       // object_templates.txt 内容是 ./object_template_0-5.pcd
 */

#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <Eigen/Core>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/fpfh.h>
#include <pcl/registration/ia_ransac.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/search/impl/search.hpp>

using namespace std;

typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> PCLHandler;

// FeatureCloud 封装的工作有 加载点云,计算法向量,计算pfh
class FeatureCloud {
public:
    FeatureCloud() {
        search_kdtree_ = pcl::search::KdTree<PointT>::Ptr(new pcl::search::KdTree<PointT>);
        normal_radius_ = 0.02f;
        feature_radius_ = 0.03f;
    }


public:
    // 直接传入点云 并处理
    void setInputCloud(PointCloudT::Ptr cloud) {
        cloud_ = cloud;

        // 处理点云(计算法向量,计算pfh)
        processPointCloud();
    }

    // 从文件中 加载 并处理
    void loadInputCloud(string pcd_filename) {
        cloud_ = PointCloudT::Ptr(new PointCloudT);
        pcl::io::loadPCDFile(pcd_filename, *cloud_);

        // 处理点云(计算法向量,计算pfh)
        processPointCloud();
    }

    void processPointCloud() {
        // 计算法向量
        normals_ = pcl::PointCloud<pcl::Normal>::Ptr(new pcl::PointCloud<pcl::Normal>);

        pcl::NormalEstimation<PointT, pcl::Normal> ne;
        ne.setInputCloud(cloud_);
        ne.setSearchMethod(search_kdtree_);
        ne.setRadiusSearch(normal_radius_);
        ne.compute(*normals_);

        // 计算pfh
        features_ = pcl::PointCloud<pcl::FPFHSignature33>::Ptr(new pcl::PointCloud<pcl::FPFHSignature33>);

        pcl::FPFHEstimation<PointT, pcl::Normal, pcl::FPFHSignature33> fpfhEstimation;
        fpfhEstimation.setInputCloud(cloud_);
        fpfhEstimation.setInputNormals(normals_);
        fpfhEstimation.setSearchMethod(search_kdtree_);
        fpfhEstimation.setRadiusSearch(feature_radius_);
        fpfhEstimation.compute(*features_);

    }

    PointCloudT::Ptr getPointCloud() {
        return cloud_;
    }

    pcl::PointCloud<pcl::FPFHSignature33>::Ptr getFeatures() {
        return features_;
    }

private:
    PointCloudT::Ptr cloud_;
    pcl::PointCloud<pcl::Normal>::Ptr normals_;
    pcl::PointCloud<pcl::FPFHSignature33>::Ptr features_;

    pcl::search::KdTree<PointT>::Ptr search_kdtree_;// 搜索方法
    float normal_radius_; // 构建法向量时 的搜索半径
    float feature_radius_; // 构建pfh时 的搜索半径
};

class TemplateAlignment {
public:
    // A struct for storing alignment results
    struct Result {
        // 匹配分数
        float fitness_score;
        // 转换矩阵
        Eigen::Matrix4f final_transformation;

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    };

    TemplateAlignment() :
            min_sample_distance_(0.05f),
            max_correspondence_distance_(0.01f * 0.01f),
            nr_iterations_(500) {
        // Intialize the parameters in the Sample Consensus Intial Alignment (SAC-IA) algorithm
        sac_ia_.setMinSampleDistance(min_sample_distance_);
        sac_ia_.setMaxCorrespondenceDistance(max_correspondence_distance_);
        sac_ia_.setMaximumIterations(nr_iterations_);
    }

public:
    void addTemplateCloud(FeatureCloud template_cloud) {
        templates_.push_back(template_cloud);
    }

    void setTargetCloud(FeatureCloud target_cloud) {
        target_ = target_cloud;
        // 设置输入target点云
        sac_ia_.setInputTarget(target_cloud.getPointCloud());
        // 设置特征target
        sac_ia_.setTargetFeatures(target_cloud.getFeatures());
    }

    // 对齐的核心代码
    void align(FeatureCloud &template_cloud, TemplateAlignment::Result &result) {
        // 设置输入源
        sac_ia_.setInputSource(template_cloud.getPointCloud());
        // 设置特征源
        sac_ia_.setSourceFeatures(template_cloud.getFeatures());

        pcl::PointCloud<pcl::PointXYZ> registration_output;
        sac_ia_.align(registration_output);

        // 根据最远相应距离计算匹配分数
        result.fitness_score = (float) sac_ia_.getFitnessScore(max_correspondence_distance_);
        // 获取最终转换矩阵
        result.final_transformation = sac_ia_.getFinalTransformation();
    }

    void alignAll(std::vector<TemplateAlignment::Result, Eigen::aligned_allocator<Result> > &results) {
        results.resize(templates_.size());
        for (size_t i = 0; i < templates_.size(); ++i) {
            align(templates_[i], results[i]);
        }
    }

    int findBestAlignment(TemplateAlignment::Result &result) {
        // Align all of the templates to the target cloud
        std::vector<Result, Eigen::aligned_allocator<Result> > results;
        alignAll(results);

        // Find the template with the best (lowest) fitness score
        float lowest_score = std::numeric_limits<float>::infinity();
        int best_template = 0;
        for (size_t i = 0; i < results.size(); ++i) {
            const Result &r = results[i];
            if (r.fitness_score < lowest_score) {
                lowest_score = r.fitness_score;
                best_template = (int) i;
            }
        }

        // Output the best alignment
        result = results[best_template];
        return (best_template);
    }

private:
    // a list of template clouds and the target to which they will be aligned
    std::vector<FeatureCloud> templates_;
    FeatureCloud target_;

    // The Sample Consensus Initial Alignment (SAC-IA) registration routine and its parameters
    pcl::SampleConsensusInitialAlignment<pcl::PointXYZ, pcl::PointXYZ, pcl::FPFHSignature33> sac_ia_;
    float min_sample_distance_;
    float max_correspondence_distance_;
    int nr_iterations_;

};

/**
 * 直通滤波，保留指定范围的点云 [limitMin, limitMax]
 */
void filterCloud(
        const pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud,
        const pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud_filtered,
        const char *filter_name, double limitMin, double limitMax) {
    pcl::PassThrough<pcl::PointXYZ> passFilter;
    passFilter.setInputCloud(cloud);
    passFilter.setFilterFieldName(filter_name);
    passFilter.setFilterLimits(limitMin, limitMax);
    passFilter.setFilterLimitsNegative(false);
    passFilter.filter(*cloud_filtered);
}

/**
 * 降采样
 */
void downsampling(pcl::PointCloud<pcl::PointXYZ>::Ptr &input_cloud, pcl::PointCloud<pcl::PointXYZ>::Ptr &output_cloud,
                  const float voxel_grid_size) {
    pcl::VoxelGrid<pcl::PointXYZ> vox_grid;
    vox_grid.setInputCloud(input_cloud);
    // 设置叶子节点的大小lx, ly, lz
    vox_grid.setLeafSize(voxel_grid_size, voxel_grid_size, voxel_grid_size);
    //vox_grid.filter (*cloud); // Please see this http://www.pcl-developers.org/Possible-problem-in-new-VoxelGrid-implementation-from-PCL-1-5-0-td5490361.html
    pcl::PointCloud<pcl::PointXYZ>::Ptr tempCloud(new pcl::PointCloud<pcl::PointXYZ>);
    vox_grid.filter(*tempCloud);
    output_cloud = tempCloud;
}

int main(int argc, char **argv) {

    if (argc < 3) {
        cout << "请把模板点云文件列表和目标点云作为参数\n" <<
             "例如:./out ../data/object_templates.txt ../data/person.pcd" << endl;
        return -1;
    }
    //1 加载并处理 模板点云
    std::vector<FeatureCloud> object_templates;
    std::ifstream input_stream(argv[1]);

    std::string pcd_filename;
    while (input_stream.good()) {
        // 读取文件的每一行
        std::getline(input_stream, pcd_filename);
        if (pcd_filename.empty() || pcd_filename.at(0) == '#') { // 如果是空行 或者是#开头
            continue;
        }

        // 加载并处理点云
        FeatureCloud template_cloud;
        template_cloud.loadInputCloud(pcd_filename);
        object_templates.push_back(template_cloud);
    }
    input_stream.close();

    //2 加载并处理目标场景点云
    PointCloudT::Ptr cloud(new PointCloudT);
    pcl::io::loadPCDFile(argv[2], *cloud);

    // 直通滤波处理目标点云
    filterCloud(cloud, cloud, "z", 0.0, 1.1); // 可以 pcl_viewer 查看(按u)
    filterCloud(cloud, cloud, "x", -1.0, 0.37);

    // 降采样
    downsampling(cloud, cloud, 0.005f);
    FeatureCloud target_cloud;
    target_cloud.setInputCloud(cloud);


    //3 进行匹配
    // 创建匹配器, 执行模板匹配
    TemplateAlignment template_align;
    // 添加模板点云
    for (FeatureCloud object_template: object_templates) {
        template_align.addTemplateCloud(object_template);
    }
    // 设置目标点云
    template_align.setTargetCloud(target_cloud);

    // 执行配准,返回最佳匹配结果
    TemplateAlignment::Result best_alignment; // 传出参数
    int best_index = template_align.findBestAlignment(best_alignment);
    FeatureCloud &best_template = object_templates[best_index];

    // Print the alignment fitness score (values less than 0.00002 are good)
    printf("Best fitness score: %f\n", best_alignment.fitness_score);
    printf("Best fitness best_index: %d\n", best_index);

    // Print the rotation matrix and translation vector
    Eigen::Matrix3f rotation = best_alignment.final_transformation.block<3, 3>(0, 0);
    Eigen::Vector3f translation = best_alignment.final_transformation.block<3, 1>(0, 3);
    Eigen::Vector3f euler_angles = rotation.eulerAngles(2, 1, 0) * 180 / M_PI;
    printf("\n");
    printf("    | %6.3f %6.3f %6.3f | \n", rotation(0, 0), rotation(0, 1), rotation(0, 2));
    printf("R = | %6.3f %6.3f %6.3f | \n", rotation(1, 0), rotation(1, 1), rotation(1, 2));
    printf("    | %6.3f %6.3f %6.3f | \n", rotation(2, 0), rotation(2, 1), rotation(2, 2));
    printf("\n");
    cout << "yaw(z) pitch(y) roll(x) = " << euler_angles.transpose() << endl;
    printf("\n");
    printf("t = < %0.3f, %0.3f, %0.3f >\n", translation(0), translation(1), translation(2));

    // Save the aligned template for visualization
    pcl::PointCloud<pcl::PointXYZ> transformed_cloud;
    // 将模板中保存的点云图进行旋转矩阵变换，把变换结果保存到transformed_cloud
    pcl::transformPointCloud(*best_template.getPointCloud(), transformed_cloud, best_alignment.final_transformation);

//    pcl::io::savePCDFileBinary("output.pcd", transformed_cloud);

    //4 可视化
    pcl::visualization::PCLVisualizer viewer("example");
    viewer.addCoordinateSystem(0.5, "cloud", 0);
    viewer.setBackgroundColor(0.05, 0.05, 0.05, 0); // Setting background to a dark grey
    //4.1 旋转后的点云rotated --------------------------------
    pcl::PointCloud<pcl::PointXYZ>::Ptr t_cloud(&transformed_cloud);
    PCLHandler transformed_cloud_handler(t_cloud, 255, 255, 255);// 白色
    viewer.addPointCloud(t_cloud, transformed_cloud_handler, "transformed_cloud");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 2, "transformed_cloud");
    //4.2 目标点云target --------------------------------
    PCLHandler target_cloud_handler(cloud, 255, 100, 100); // 红色
    viewer.addPointCloud(cloud, target_cloud_handler, "target_cloud");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "target_cloud");

    //4.3 模板点云template --------------------------------
    PCLHandler template_cloud_handler(cloud, 100, 100, 255); // 蓝色
    viewer.addPointCloud(best_template.getPointCloud(), template_cloud_handler, "template_cloud");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "template_cloud");

    while (!viewer.wasStopped()) { // Display the visualiser until 'q' key is pressed
        viewer.spinOnce();
    }


    return 0;
}

