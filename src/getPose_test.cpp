#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "gazebo_msgs/ModelStates.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "tf/transform_datatypes.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/LinearMath/Matrix3x3.h"

#define NUM_ROBOT 2
#define OFFS 1      // because the first entry in modelstates is ground plane
# define M_PI 3.14159265358979323846



void chatterCallback(const gazebo_msgs::ModelStates::ConstPtr& msg)
{
    // std::cout << msg->name[0] << std::endl;
    // std::cout << msg->name[1] << std::endl;
    // std::cout << msg->name[2] << std::endl;
    // std::cout << msg->name.size() << std::endl;

    for(int i=OFFS; i<OFFS+NUM_ROBOT; i++)   {
        std::cout << msg->name[i] << " position and orientation" << std::endl;
        std::cout << msg->pose[i].position << std::endl;

        // convert to RPY
        tf::Quaternion quat;
        tf::quaternionMsgToTF(msg->pose[i].orientation, quat);

        double roll, pitch, yaw;
        tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

        geometry_msgs::Vector3 rpy;
        rpy.x = roll;
        rpy.y = pitch;
        rpy.z = yaw;

        // std::cout << msg->name[i] << " yaw" << ": " << yaw * 180.0/M_PI << std::endl;


    }





}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "getPose");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/gazebo/model_states", 100, chatterCallback);

  ros::spin();
}
