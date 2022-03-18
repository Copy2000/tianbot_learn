#include "ros/ros.h"
#include "geometry_msgs/Twist.h"


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "tianbot_Vel");
    ros::NodeHandle nh;
    ros::Publisher Pub = nh.advertise<geometry_msgs::Twist>("/tianbot_mini/cmd_vel",10);

    geometry_msgs::Twist twist;
    ros::Rate loop_rate(10);
    while (ros::ok())
    {

        ROS_INFO("\ntwist.linear.x = %f;\n twist.angular.z = %f;\n",twist.linear.x,twist.angular.z);
        
        twist.linear.x = 5;
        twist.angular.z = 2;
        Pub.publish(twist);

        loop_rate.sleep();
        ros::spinOnce();

    }
    
    
    return 0;
}