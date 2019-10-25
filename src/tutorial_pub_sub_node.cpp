#include <cmath>

#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

const double dist_min = 0.1;

double dist;
turtlesim::Pose pose_desired;
geometry_msgs::Twist cmd_vel;

// Callback function to update command velocities depending on updated pose information
void poseCallback(const turtlesim::Pose &pose)
{
    dist = std::sqrt(std::pow(pose_desired.x-pose.x, 2.0) + std::pow(pose_desired.y-pose.y, 2.0));

    if(dist > dist_min)
    {
        cmd_vel.linear.x = dist;
        cmd_vel.angular.z = 3.0 * (std::atan2(pose_desired.y-pose.y, pose_desired.x-pose.x) - pose.theta);
    }
    else
    {
        cmd_vel.linear.x = 0.0;
        cmd_vel.angular.z = 0.0;
    }
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "tutorial_pub_sub");
    ros::NodeHandle nh;

    // Create a Subscriber object
    // subscribe() returns a Subscriber for the topic 'pose' with a queue size of 10 messages
    // The third argument is the callback function handle 'poseCallback' that will be passed incoming messages
    ros::Subscriber pose_sub = nh.subscribe("pose", 10, &poseCallback);
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    ros::Rate loop_rate(10.0);

    // Private handle for the current node namespace
    // Access parameters found in /<node_name>/<param_name> e.g. /tutorial_pub_sub/axis_linear 
    ros::NodeHandle nh_priv("~");
    nh_priv.param<double>("desired_x", pose_desired.x, 2.0);
    nh_priv.param<double>("desired_y", pose_desired.y, 2.0);

    // Desired pose for turtle
    pose_desired.theta = 0.0;
    cmd_vel.linear.x = 0.0, cmd_vel.angular.z = 0.0;
    
    int count = 1;
    while(ros::ok())
    {
        cmd_vel_pub.publish(cmd_vel);
        ROS_INFO("[%d] dist %lf", count, dist);

        if(dist > dist_min)
        {
            ++count;
        }

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

