#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
  ROS_INFO_STREAM("Try sending request to move the robot.");

  // Create a request
  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  // Call the command_robot service with request values given above
  if (!client.call(srv))
    ROS_ERROR("Failed to call service /ball_chaser/command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image& img)
{
  enum Side : uint8_t {LEFT, MID, RIGHT, NO_BALL} side = NO_BALL;

  // Determine if there is a white ball and if yes, on which side
  for (int i = 0; i < img.height * img.step; i+=3) {
    auto red   = img.data[i];
    auto green = img.data[i+1];
    auto blue  = img.data[i+2];

    if (red == 255 && green == 255 && blue == 255) {
      auto col = i % img.step;
      if (col < img.step * 0.4) {
        side = LEFT;
      } else if (col > img.step * 0.6) {
        side = RIGHT;
      } else {
        side = MID;
      }
      break;
    }
  }

  // Drive robot towards the ball
  if (side == LEFT) {
    drive_robot(0.5, 1.0);
  } else if (side == RIGHT) {
    drive_robot(0.5, -1.0);
  } else if (side == MID) {
    drive_robot(0.5, 0.0);
  } else /* NO_BALL */ {
    drive_robot(0.0, 0.0);
  }
}

int main(int argc, char** argv)
{
  // Initialize the process_image node and create a handle to it
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  // Define a client service capable of requesting services from command_robot
  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

  // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
  ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  // Handle ROS communication events
  ros::spin();

  return 0;
}