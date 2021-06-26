//
// Created by zcb on 6/26/21.
//

#ifndef VELODYNE_PLUGIN_PLUGIN_H
#define VELODYNE_PLUGIN_PLUGIN_H

#include <iostream>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/transport/transport.hh>

#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <thread>
#include <ros/subscribe_options.h>
#include <std_msgs/Float32.h>

class VelodynePlugin : public gazebo::ModelPlugin {
public:
    VelodynePlugin() {

    }

    virtual void Load(gazebo::physics::ModelPtr model, sdf::ElementPtr sdf);

    void setVelocity(const double &v);

    void createSubscriber();

private:
    gazebo::physics::ModelPtr model;
    boost::shared_ptr<gazebo::physics::Joint> joint;
    gazebo::transport::NodePtr node;
    gazebo::transport::SubscriberPtr sub;

    std::unique_ptr<ros::NodeHandle> rosNode;
    ros::Subscriber rosSub;
    ros::CallbackQueue rosQueue;
    std::thread rosQueueThread;

    void callback(const std_msgs::Float32::ConstPtr &_msg) {
        this->setVelocity(_msg->data);
    }

    void queueThread() {
        static const double timeout = 0.01;
        while (this->rosNode->ok()) {
            this->rosQueue.callAvailable(ros::WallDuration(timeout));
        }
    }

};

GZ_REGISTER_MODEL_PLUGIN(VelodynePlugin);
#endif //VELODYNE_PLUGIN_PLUGIN_H
