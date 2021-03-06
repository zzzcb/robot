#include <iostream>

// ros
#include <ros/ros.h>

// MoveIt
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_visual_tools/moveit_visual_tools.h>


#include <geometric_shapes/shape_operations.h> // 用于处理dae 文件
#include <tf2_geometry_msgs/tf2_geometry_msgs.h> //用于转换 rpy -> 四元数

/*
    1, Rviz 场景搭建 : 物料架(使用dae),物料(a box)，物料摆放的位置
    2, Moveit 运动规划 
    3, Gazebo中验证是否成功 
*/

const std::string STAGE_GROUP = "stage_group";
const std::string ARM_GROUP = "arm_group";
const std::string GRIPPER_GROUP = "gripper_group";

const std::string SHELF_MESH_PATH = "package://common_pkg/meshes/shelf.dae";
const std::string BELT_MESH_PATH = "package://common_pkg/meshes/belt.dae";

// rviz中 场景构造:添加物料架
void addShelf(moveit::planning_interface::MoveGroupInterface &group,
              moveit::planning_interface::PlanningSceneInterface &scene) {
    std::vector<moveit_msgs::CollisionObject> objects;
    objects.resize(1);    // 总共只有一个 物料架


    //1 对 objects[0] 进行基础设置
    objects[0].id = "shelf";
    objects[0].operation = objects[0].ADD;
    objects[0].header.frame_id = group.getPlanningFrame();

    // 位姿信息
    geometry_msgs::Pose pose;
    pose.position.x = -0.6;
    pose.position.y = 0;
    pose.position.z = 0;
    pose.orientation.w = 1.0;
    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;

    objects[0].mesh_poses.resize(1); // objects[0]只有一个mesh
    objects[0].mesh_poses[0].position = pose.position;
    objects[0].mesh_poses[0].orientation = pose.orientation;

    //2 dae加载
    shapes::Mesh *m = shapes::createMeshFromResource(SHELF_MESH_PATH);
    shapes::ShapeMsg meshMsg;// meshMsg 更为通用,可以转换为三种格式: shape_msgs::SolidPrimitive, shape_msgs::Mesh, shape_msgs::Plane
    shapes::constructMsgFromShape(m, meshMsg);

    shape_msgs::Mesh mesh = boost::get<shape_msgs::Mesh>(meshMsg);// 将通用的 meshMsg 转为我们需要的 shape_msgs::Mesh

    //3 继续对 objects[0] 进行属性设置
    objects[0].meshes.resize(0);
    objects[0].meshes.push_back(mesh);

    //4 将objects 添加到 scene
    scene.addCollisionObjects(objects);

}


float box_x = 0.06;
float box_y = 0.06;
float box_z = 0.16;

// rviz中 场景构造:添加物料(a box)
void addMaterial(moveit::planning_interface::MoveGroupInterface &group,
                 moveit::planning_interface::PlanningSceneInterface &scene) {
    //1 获取 x y z 坐标(scripts 中 load_material.py 脚本已经上传了 x y z )
    float x, y, z;
    ros::param::get("/target_pos/x", x);
    ros::param::get("/target_pos/y", y);
    ros::param::get("/target_pos/z", z);
    //std::cout << x << y << z << std::endl;


    //2 对 objects[0] 进行基础设置
    std::vector<moveit_msgs::CollisionObject> objects;
    objects.resize(1);    // 总共只有一个 物料(a box)

    objects[0].id = "material";
    objects[0].operation = objects[0].ADD;
    objects[0].header.frame_id = group.getPlanningFrame();

    // 形状信息
    objects[0].primitives.resize(1); // 只有一个primitive
    objects[0].primitives[0].type = objects[0].primitives[0].BOX;
    objects[0].primitives[0].dimensions.resize(3); // 3 个维度
    objects[0].primitives[0].dimensions[0] = box_x; // box 的x y z 长度
    objects[0].primitives[0].dimensions[1] = box_y;
    objects[0].primitives[0].dimensions[2] = box_z;

    // 位姿信息
    geometry_msgs::Pose pose;
    pose.position.x = x;
    pose.position.y = y;
    pose.position.z = z + box_z / 2;
    pose.orientation.w = 1.0;
    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;

    objects[0].primitive_poses.resize(1); // 只有一个 primitive
    objects[0].primitive_poses[0].position = pose.position;
    objects[0].primitive_poses[0].orientation = pose.orientation;


    //3 加入到场景中
    scene.addCollisionObjects(objects);

}

// rviz中 场景构造:添加传送带
void addBelt(moveit::planning_interface::MoveGroupInterface &group,
              moveit::planning_interface::PlanningSceneInterface &scene) {
    std::vector<moveit_msgs::CollisionObject> objects;
    objects.resize(1);  

    //1 对 objects[0] 进行基础设置
    objects[0].id = "belt";
    objects[0].operation = objects[0].ADD;
    objects[0].header.frame_id = group.getPlanningFrame();

    // 位姿信息
    geometry_msgs::Pose pose;
    pose.position.x = 0.65;
    pose.position.y = -0.5;
    pose.position.z = 0;
    pose.orientation.w = 0.707;
    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = -0.707;

    objects[0].mesh_poses.resize(1); // objects[0]只有一个mesh
    objects[0].mesh_poses[0].position = pose.position;
    objects[0].mesh_poses[0].orientation = pose.orientation;

    //2 dae加载
    shapes::Mesh *m = shapes::createMeshFromResource(BELT_MESH_PATH);
    shapes::ShapeMsg meshMsg;// meshMsg 更为通用,可以转换为三种格式: shape_msgs::SolidPrimitive, shape_msgs::Mesh, shape_msgs::Plane
    shapes::constructMsgFromShape(m, meshMsg);

    shape_msgs::Mesh mesh = boost::get<shape_msgs::Mesh>(meshMsg);// 将通用的 meshMsg 转为我们需要的 shape_msgs::Mesh

    //3 继续对 objects[0] 进行属性设置
    objects[0].meshes.resize(0);
    objects[0].meshes.push_back(mesh);

    //4 将objects 添加到 scene
    scene.addCollisionObjects(objects);
}


// 对 stage 进行运动规划
void moveStage(moveit::planning_interface::MoveGroupInterface &group) {
    //1 将stage 移动至与 目标物料 y 坐标一致 
    float y;
    ros::param::get("/target_pos/y", y);

    //2 设置joint (正向运动学)
    std::vector<double> jointValues;
    jointValues = group.getCurrentJointValues();
    jointValues[0] = y;
    group.setJointValueTarget(jointValues);

    //3 进行运动规划
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    const moveit::planning_interface::MoveItErrorCode &code = group.plan(plan);
    if (code) {
        // 规划成功
        group.move();
    } else {
        // 规划失败
        ROS_ERROR("move stage failed!");
    }
}
 

// traj 为输出参数
void getGripperJointTrajMsg(trajectory_msgs::JointTrajectory &traj, double position) {
    //open  状态时 四个joint的大小  0.86,-0.86,-0.86,0.86
    //close 状态时 四个joint的大小  0.02,-0.02,-0.02,0.02
    traj.joint_names.resize(4);
    traj.joint_names[0] = "Link1"; //吐槽: 命名的人就是个奇葩,joint也命名为 Link!
    traj.joint_names[1] = "Link11";
    traj.joint_names[2] = "Link2";
    traj.joint_names[3] = "Link22";

    traj.points.resize(1); // traj 只有一个轨迹点
    traj.points[0].positions.resize(4);
    traj.points[0].positions[0] = position;
    traj.points[0].positions[1] = (-1) * position;
    traj.points[0].positions[2] = (-1) * position;
    traj.points[0].positions[3] = position;

    traj.points[0].time_from_start = ros::Duration(0.5); // 执行时间 0.5s

}

// traj 为输出参数
void getGripperOpenMsg(trajectory_msgs::JointTrajectory &traj) {
    getGripperJointTrajMsg(traj, 0.02); 
}

// traj 为输出参数
void getGripperCloseMsg(trajectory_msgs::JointTrajectory &traj) {
    getGripperJointTrajMsg(traj, 0.135); // 0.86 位完全关闭
}

const float x_dis_to_obj = 0.15; // arm ee_link 原点 到 物体中心点的安全距离,eg2的夹爪的palm 长度是0.1
// rviz中 抓取物体 并在gazebo中验证
void pick(moveit::planning_interface::MoveGroupInterface &group) {
    //1 目标位置 ,已经存在与 param server了
    float x, y, z;
    ros::param::get("/target_pos/x", x);
    ros::param::get("/target_pos/y", y);
    ros::param::get("/target_pos/z", z);

    //2 设置Grasp消息
    std::vector<moveit_msgs::Grasp> grasps;
    grasps.resize(1); // 一个抓取 位姿
    //2.1 arm ee_link 要到达的位姿
    grasps[0].grasp_pose.header.frame_id = group.getPlanningFrame();
    grasps[0].grasp_pose.pose.position.x = x + x_dis_to_obj;
    grasps[0].grasp_pose.pose.position.y = y;
    grasps[0].grasp_pose.pose.position.z = z + box_z / 2;
    tf2::Quaternion qua;
    qua.setRPY(M_PI, 0, -M_PI); // 当前arm ee_link 的姿态是 PI,0,-PI,可以自己分析urdf,也可以通过代码 group.getCurrentRPY()来知道
    grasps[0].grasp_pose.pose.orientation.w = qua.w();
    grasps[0].grasp_pose.pose.orientation.x = qua.x();
    grasps[0].grasp_pose.pose.orientation.y = qua.y();
    grasps[0].grasp_pose.pose.orientation.z = qua.z();

    //2.2 接近 shelf 的姿势
    grasps[0].pre_grasp_approach.direction.header.frame_id = group.getPlanningFrame();
    grasps[0].pre_grasp_approach.direction.vector.x = -1.0; // x 轴负向
    grasps[0].pre_grasp_approach.min_distance = 0.03;
    grasps[0].pre_grasp_approach.desired_distance = 0.05;

    //2.3 打开夹爪,夹取前的 Gripper 的Msg
    getGripperOpenMsg(grasps[0].pre_grasp_posture); // 会给 pre_grasp_posture 赋值

    //2.4 关闭夹爪,夹取后的 Gripper 的Msg
    getGripperCloseMsg(grasps[0].grasp_posture); // 会给 grasp_posture 赋值

    //2.4 离开 shelf 的姿势
    grasps[0].post_grasp_retreat.direction.header.frame_id = group.getPlanningFrame();
    grasps[0].post_grasp_retreat.direction.vector.z = 1.0; // z 轴正向
    grasps[0].post_grasp_retreat.min_distance = 0.05;
    grasps[0].post_grasp_retreat.desired_distance = 0.1;

    //3 执行pick
    group.setSupportSurfaceName("shelf");
    group.pick("material", grasps);

}

void reUp(moveit::planning_interface::MoveGroupInterface &group) {
    //因为gazebo导致moveit attach失败,所以需要我们手动自己 向上抬起  0.05
    //1 设置start state
    group.setStartState(*group.getCurrentState());
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    
    //2 设置target pose
    geometry_msgs::PoseStamped curPose = group.getCurrentPose();
    geometry_msgs::Pose p;
    p.position.x = curPose.pose.position.x;
    p.position.y = curPose.pose.position.y;
    p.position.z = curPose.pose.position.z + 0.05;
    p.orientation.w = curPose.pose.orientation.w;
    p.orientation.x = curPose.pose.orientation.x;
    p.orientation.y = curPose.pose.orientation.y;
    p.orientation.z = curPose.pose.orientation.z;
    group.setPoseTarget(p);
    
    //3 执行规划
    const moveit::planning_interface::MoveItErrorCode &code = group.plan(plan);
    if(code){
        group.execute(plan);
    }else{
        ROS_ERROR("reUp motion failed");
    }
}

void moveToBelt(moveit::planning_interface::MoveGroupInterface &group) {
    //1 滑轨先移动到 -0.2(y)
    float slide_tar_y =  -0.2;
    std::vector<double> jointValues;
    jointValues = group.getCurrentJointValues();
    jointValues[0] = slide_tar_y;
    group.setJointValueTarget(jointValues);

    
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    const moveit::planning_interface::MoveItErrorCode &code = group.plan(plan);
    if(code){ // 规划成功
        group.execute(plan);
    }else{
        std::cout<<"移动到传送带附近失败..." << std::endl;
    }

}

void place(moveit::planning_interface::MoveGroupInterface &group) {
    group.allowReplanning(true);
    //group.setGoalPositionTolerance(0.01);//m
    //group.setGoalOrientationTolerance(0.01);//rad

    // 1、放置物体的位置
    std::vector<moveit_msgs::PlaceLocation> places;
    places.resize(1);
    places[0].place_pose.header.frame_id=group.getPlanningFrame();

    tf2::Quaternion qua;
    qua.setRPY(0,0,M_PI);
    places[0].place_pose.pose.orientation.w=qua.w();
    places[0].place_pose.pose.orientation.x=qua.x();
    places[0].place_pose.pose.orientation.y=qua.y();
    places[0].place_pose.pose.orientation.z=qua.z();

    places[0].place_pose.pose.position.x= 0.5;
    places[0].place_pose.pose.position.y= -0.5;
    places[0].place_pose.pose.position.z= 0.2 + box_z/2;
    
    // 2、接近传送带的 姿势 
    places[0].pre_place_approach.direction.header.frame_id=group.getPlanningFrame();
    places[0].pre_place_approach.direction.vector.x=1.0;
    places[0].pre_place_approach.min_distance=0.05;
    places[0].pre_place_approach.desired_distance=0.08;

    // 3、打开夹⼦
    getGripperOpenMsg(places[0].post_place_posture);

    // 4、离开传送带的 姿势 
    places[0].post_place_retreat.direction.header.frame_id=group.getPlanningFrame();
    places[0].post_place_retreat.direction.vector.x=-1.0;
    places[0].post_place_retreat.min_distance=0.08;
    places[0].post_place_retreat.desired_distance=0.12;

    group.setSupportSurfaceName("belt");
    group.place("material",places);
}

void take_out(moveit::planning_interface::MoveGroupInterface &group) {

    group.setStartStateToCurrentState(); 

    //1 先沿 x轴负向 抽取出来
    std::vector<geometry_msgs::Pose> wayPoints;
    double eff_step=0.005;
    double jump_threshold=0.0;
    moveit_msgs::RobotTrajectory trajectory;

    // 构建wayPoints
    geometry_msgs::Pose p = group.getCurrentPose().pose;
    //wayPoints.push_back(p); 
    p.position.x += 0.2;
    wayPoints.push_back(p);

    int cnt=0;
    int max=100; // 最多重试100次
    double rate = 0;
    while(rate<1.0 && cnt<max ){ // 如果rate 不是100%,而且也可以重试
        rate = group.computeCartesianPath(wayPoints,eff_step,jump_threshold,trajectory);//trajectory 为输出参数,
        cnt++;
    }
    if(rate == 1.0){
        //规划成功
        ROS_INFO_STREAM("CartesianPaht successed,final cnt is "<<cnt); // 最终尝试了多少次
        moveit::planning_interface::MoveGroupInterface::Plan plan;
        plan.trajectory_ = trajectory;
        group.execute(plan);

    }else{
        ROS_INFO_STREAM("CartesianPaht failed,final rate is "<<rate<<" | cnt is "<<cnt); // 最后的 rate 值
    }
}

int main(int argc, char **argv) {
    //1 初始化节点
    ros::init(argc, argv, "planning_scene_ros_api_tutorial");
    ros::NodeHandle nh;

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //2 setup
    moveit::planning_interface::MoveGroupInterface armGroup(ARM_GROUP);
    std::string armPlanningFrame = armGroup.getPlanningFrame();
    moveit_visual_tools::MoveItVisualTools mvt(armPlanningFrame);

    moveit::planning_interface::PlanningSceneInterface scene;

    //3 一上来先删除 shelf 和 material,方便循环调试
    mvt.prompt("remove shelf and material");
    std::vector<std::string> ids = {"shelf", "material","belt"};
    scene.removeCollisionObjects(ids);

    //4 添加物料架 (dae 文件)
    mvt.prompt("add a shelf");
    addShelf(armGroup, scene);


    //5 添加物料
    mvt.prompt("add material(a box)");
    addMaterial(armGroup, scene);

    //6 添加传送带 (dae 文件)
    mvt.prompt("add a belt");
    addBelt(armGroup, scene);

    //7 对stage 进行运动规划
    mvt.prompt("move stage");
    moveit::planning_interface::MoveGroupInterface stageGroup(STAGE_GROUP);
    moveStage(stageGroup);

    //8 pick material
    mvt.prompt("pick material");
    pick(armGroup);

    //9 判断material是否 被attach,(gazebo中可能导致无法attach)
    const std::map<std::string, moveit_msgs::AttachedCollisionObject> &map = scene.getAttachedObjects({"material"});
    //for(auto i = map.begin();i!=map.end();i++){
    //    std::cout << i->first <<"  | " << i->second << std::endl;
    //}
    if(map.empty()){ // 没有attach  ,需要我们手动attach,并抬起
        mvt.prompt("re motion planning");
        armGroup.attachObject("material"); // 默认将material attach到 ee_link
        reUp(armGroup); // 手动抬升,再次规划
    }

    //10 take out material,拿出一段距离
    mvt.prompt("take out material a distance");
    take_out(armGroup); 

    //11 移动到传送带附近
    mvt.prompt("move to belt neighbor");
    moveToBelt(stageGroup);

    //12 放置物料
    mvt.prompt("place material to belt");
    place(armGroup);

    mvt.prompt("done");
    //ros::waitForShutdown();

    return 0;
}

