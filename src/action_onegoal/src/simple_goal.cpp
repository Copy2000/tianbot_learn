#include <iostream>
#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/Twist.h"
#include "actionlib/server/simple_action_server.h"
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "move_base_msgs/MoveBaseGoal.h"

//https://blog.csdn.net/lzy6041/article/details/120235654
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "simple_goal");
    ros::NodeHandle nh;
    //订阅movebase操作服务器
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> move_base("move_base",true);

    ROS_INFO("waiting movebase server.");
    if(!move_base.waitForServer(ros::Duration(5)))
    {
        ROS_INFO("not connect movebase server.");
        return 1;
    }
    ROS_INFO("connected movebase server success.");
    ROS_INFO("beginning navigation");
    geometry_msgs::Pose pose;
    pose.position.x = 2;
    pose.orientation.w = 1;
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    goal.target_pose.pose = pose;
    //将目标位姿发送到MoveBaseAction服务器
    ROS_INFO("Sending Goal!!");
    move_base.sendGoal(goal);

    //5分钟限制，查看是否成功到达
    bool finished_within_time =  move_base.waitForResult(ros::Duration(300));
    if(!finished_within_time)
    {
        move_base.cancelGoal();
        ROS_INFO("Time out achieving goal!!");
    }
    else
    {
        if(move_base.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            ROS_INFO("Goal succeeded!!");
        }
        else
        {
            ROS_INFO("Goal failed!!");
        }
    }
    ros::spin();
    ROS_INFO("Time out achieving goal!!");
    return 0;
}