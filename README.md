# Project 2: Go Chase It

Use ROS and Gazebo to build a mobile robot for chasing a white ball.

<a href="https://www.youtube.com/watch?v=fugrDDqZiU8&" target="_blank">
<img src="demo.gif" alt="demo" width="500" height="280"/></a>

## Structure
```
.RoboND-Go-Chase-It                # Go Chase It Project
├── my_robot                       # my_robot package
│   ├── launch                     # launch folder for launch files
│   │   ├── robot_description.launch
│   │   ├── world.launch
│   ├── meshes                     # meshes folder for sensors
│   │   ├── hokuyo.dae
│   ├── urdf                       # urdf folder for xarco files
│   │   ├── my_robot.gazebo
│   │   ├── my_robot.xacro
│   ├── world                      # world folder for world files
│   │   ├── UdacityOffice.world
│   ├── CMakeLists.txt             # compiler instructions
│   ├── package.xml                # package info
├── ball_chaser                    # ball_chaser package
│   ├── launch                     # launch folder for launch files
│   │   ├── ball_chaser.launch
│   ├── src                        # source folder for C++ scripts
│   │   ├── drive_bot.cpp
│   │   ├── process_images.cpp
│   ├── srv                        # service folder for ROS services
│   │   ├── DriveToTarget.srv
│   ├── CMakeLists.txt             # compiler instructions
│   ├── package.xml                # package info
└──
```
**my_robot**: This package defines the world and the robot.

**ball_chaser**: This package contains two ROS nodes for commanding the robot to chase the white ball.

## Prerequisites
 
1. Install Gazebo and [ROS](http://wiki.ros.org/ROS/Installation) on Linux.
2. Install `sudo apt-get install ros-${ROS_DISTRO}-gazebo-ros-pkgs`
(If you are using gazebo11 it should be `sudo apt-get install ros-${ROS_DISTRO}-gazebo11-ros-pkgs`)
3. Cmake and gcc/g++

## Build and Launch

1. Clone and initialize project with a catkin workspace
```console
$ mkdir catkin_ws && cd catkin_ws
$ git clone https://github.com/huuanhhuynguyen/RoboND-Go-Chase-It.git
$ mv RoboND-Go-Chase-It src
$ cd src && catkin_init_workspace
```

2. Move back to `catkin_ws\` and build
```
$ cd ..
$ catkin_make
```

3. Launch the world
```
$ source devel/setup.bash
$ roslaunch my_robot world.launch
```

4. Open another terminal (Ctrl+Shift+T), and launch the `ball_chaser` package
```
$ source devel/setup.bash
$ roslaunch ball_chaser ball_chaser.launch
```

5. Play around! Pick up the white ball and place in front of the mobile robot. The robot will follow the ball.
