#include <geometry_msgs/Twist.h>
#include <ros/ros.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "tutorial_pub");
    ros::NodeHandle nh;

    // Create a Publisher object
    // advertise() returns a Publisher of message type Twist on topic '/turtle1/cmd_vel' with a buffer of 10 messages
    ros::Publisher cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    // Loop of 1Hz 
    ros::Rate loop_rate(1.0);

    geometry_msgs::Twist cmd_vel;
    // Modify velocity commands and observe different behaviours
    cmd_vel.linear.x = 0.25; 
    cmd_vel.angular.z = 0.5;

    int count = 1;
    // Condition check that node is running fine
    while(ros::ok())
    {
        // Publish a message on the advertised topic
        cmd_vel_pub.publish(cmd_vel);
        ROS_INFO("cmd_vel %d", count);

        ++count;

        // Call all callbacks once at this point in time
        ros::spinOnce();
        // Sleep for time remaining until 1Hz rate is hit
        loop_rate.sleep();
    }

    return 0;
}

