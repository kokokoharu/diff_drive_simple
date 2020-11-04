#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelStates.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"

#define NUM_ROBOT 2
#define OFFS 1      // because the first entry in modelstates is ground plane



void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
{
    // std::cout << msg->name[0] << std::endl;
    // std::cout << msg->name[1] << std::endl;
    // std::cout << msg->name[2] << std::endl;
    // std::cout << msg->name.size() << std::endl;

    for(int i=OFFS; i<OFFS+NUM_ROBOT; i++)   {
        std::cout << i << "-th position and orientation" << std::endl;
        std::cout << msg->pose[i] << std::endl;

    }




}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/gazebo/model_states", 100, chatterCallback);

  ros::spin();
}
