#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// A callback function that executes whenever a drive_bot service is requested
bool handle_drive_request(ball_chaser::DriveToTarget::Request& req,
                          ball_chaser::DriveToTarget::Response& res)
{
  auto linear_x = (float)req.linear_x;
  auto angular_z = (float)req.angular_z;

  ROS_INFO("DriveToTargetRequest received - linear_x:%1.2f, angular_z:%1.2f", linear_x, angular_z);

  // Create a motor_command object of type geometry_msgs::Twist
  geometry_msgs::Twist motor_command;
  // Set wheel velocities and yaw orientation
  motor_command.linear.x = linear_x;
  motor_command.angular.z = angular_z;
  // Publish angles to drive the robot
  motor_command_publisher.publish(motor_command);

  // Return a response message
  res.msg_feedback = "Move command is set - linear_x: " + std::to_string(linear_x)
                                     + " , angular_z: " + std::to_string(angular_z);
  ROS_INFO_STREAM(res.msg_feedback);

  return true;
}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::ServiceServer service = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    ROS_INFO("Ready to send commands for moving the robot");

    // Handle ROS communication events
    ros::spin();

    return 0;
}
