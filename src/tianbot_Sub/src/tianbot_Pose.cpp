#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Twist.h"

void PoseCallBack(const nav_msgs::OdometryConstPtr& msg)
{
    ROS_INFO("turtle position is:\t x = %f;\t y = %f\n",msg->pose.pose.position.x,msg->pose.pose.position.y);
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "tianbot_Pose");
    ros::NodeHandle nh;
    ros::Subscriber Sub = nh.subscribe("/tianbot_mini/odom",1,PoseCallBack);
    ros::spin();
    return 0;
}