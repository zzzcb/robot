//
// Created by zcb on 6/26/21.
//

#ifndef VELODYNE_PLUGIN_PLUGIN_H
#define VELODYNE_PLUGIN_PLUGIN_H

#include <iostream>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/transport/transport.hh>

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

    void callback(ConstVector3dPtr &_msg) {
        this->setVelocity(_msg->x());
    }

};

GZ_REGISTER_MODEL_PLUGIN(VelodynePlugin);
#endif //VELODYNE_PLUGIN_PLUGIN_H
