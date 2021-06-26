//
// Created by zcb on 6/26/21.
//

#include "plugin.h"

// 注意 Load函数中不能被 阻塞
void VelodynePlugin::Load(gazebo::physics::ModelPtr model, sdf::ElementPtr sdf) {
    // 获取Joint
    if (model->GetJointCount() == 0) {
        std::cerr << "Invalid joint count, Velodyne plugin not loaded" << std::endl;
        return;
    }
    // 读取速度配置信息
    double velocity = 0;
    if (sdf->HasElement("velocity")) {
        velocity = sdf->Get<double>("velocity");
    }

    const boost::shared_ptr<gazebo::physics::Joint> &joint = model->GetJoints()[0];

    // 2.获取控制器
    const gazebo::physics::JointControllerPtr &controller = model->GetJointController();
    // 3.速度控制
    const std::string scropName = joint->GetScopedName();
    const gazebo::common::PID &pid = gazebo::common::PID(0.1);
    controller->SetVelocityPID(scropName, pid);// 添加P-controller
    controller->SetVelocityTarget(scropName, velocity);

    this->model = model;
    this->joint = joint;

    this->createSubscriber();
}

// 因为Load函数中不能被 阻塞,所以ros::spin() 不可以放在createSubscriber() 末尾,解决方法是:自定义消息队列+线程
//void VelodynePlugin::createSubscriber() {
//    this->node = gazebo::transport::NodePtr(new gazebo::transport::Node());
//    this->node->Init(this->model->GetWorld()->Name());
//
//    std::string topicName = "/vel_cmd";
//    this->sub = this->node->Subscribe(topicName, &VelodynePlugin::callback, this);
//}

// 使用ros 发布topic 速度
void VelodynePlugin::createSubscriber() {
    int argc = 0;
    char **argv = NULL;
    std::string nodeName = "gazebo_client";
    std::string topicName = "/vel_cmd";

    ros::init(argc, argv, nodeName);
    this->rosNode.reset(new ros::NodeHandle(nodeName));

    ros::SubscribeOptions so = ros::SubscribeOptions::create<std_msgs::Float32>(topicName, 1,
                                                                                boost::bind(&VelodynePlugin::callback, this, _1),
                                                                                ros::VoidPtr(),
                                                                                &this->rosQueue);
    this->rosSub = this->rosNode->subscribe(so);
    // 开启一个子线程
    this->rosQueueThread = std::thread(boost::bind(&VelodynePlugin::queueThread, this));

}


void VelodynePlugin::setVelocity(const double &v) {
    this->model->GetJointController()->SetVelocityTarget(this->joint->GetScopedName(), v);

    std::cout << "set Velocity: " << std::to_string(v) << std::endl;
}



