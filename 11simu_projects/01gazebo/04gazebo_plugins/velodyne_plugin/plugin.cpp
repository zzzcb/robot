//
// Created by zcb on 6/26/21.
//

#include "plugin.h"

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

void VelodynePlugin::createSubscriber() {
    this->node = gazebo::transport::NodePtr(new gazebo::transport::Node());
    this->node->Init(this->model->GetWorld()->Name());

    std::string topicName = "/vel_cmd";
    this->sub = this->node->Subscribe(topicName, &VelodynePlugin::callback, this);
}

void VelodynePlugin::setVelocity(const double &v) {
    this->model->GetJointController()->SetVelocityTarget(this->joint->GetScopedName(), v);

    std::cout << "set Velocity: " << std::to_string(v) << std::endl;
}



