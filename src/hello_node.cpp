#include <ros/ros.h>

int main(int argc, char *argv[])
{
    // Initialise our ROS node
    ros::init(argc, argv, "hello");
    // Create a handle to start and shutdown your node
    ros::NodeHandle nh;

    // Printing function
    ROS_INFO("Hello ROS!");

    // Loops and checks for callbacks continuously, awaits stop signal (e.g. Ctrl-C) to exit
    ros::spin();

    return 0;
}