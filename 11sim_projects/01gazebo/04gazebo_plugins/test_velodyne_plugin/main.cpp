#include <iostream>

#include <gazebo/gazebo_config.h>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <gazebo/gazebo_client.hh>


using namespace gazebo;

int main(int argc, char **argv) {
    client::setup(argc, argv);

    transport::NodePtr node(new transport::Node());
    node->Init();

    transport::PublisherPtr pub = node->Advertise<msgs::Vector3d>("/vel_cmd");
    pub->WaitForConnection();

    msgs::Vector3d msg;
    msgs::Set(&msg, ignition::math::Vector3d(std::atof(argv[1]), 0, 0));
    pub->Publish(msg);

    client::shutdown();
    return 0;
}
