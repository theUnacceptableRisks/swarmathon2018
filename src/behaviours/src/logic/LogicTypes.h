#ifndef logictypes_h
#define logictypes_h

#include <vector>
#include <geometry_msgs/Pose2D.h>
#include "../Tag.h"
#include "../Gripper.h"
#include"../waypoints/Waypoint.h"

typedef struct logic_inputs
{
    geometry_msgs::Pose2D	raw_odom;
    geometry_msgs::Pose2D	odom_accel;
    geometry_msgs::Pose2D	odom_accel_gps;
    std::vector<Tag> 		tags;
    double			us_left = 0.0;
    double			us_right = 0.0;
    double			us_center = 0.0;
    double			linear_vel_odom_accel = 0.0;
    double			linear_vel_odom_accel_gps = 0.0;
    double			angular_vel_odom_accel = 0.0;
    double			angular_vel_odom_accel_gps = 0.0;
    ros::Time			time;
} LogicInputs;

typedef struct logic_outputs
{
    Gripper::Position gripper_position = HOVER_OPEN;
    Waypoint *current_waypoint = 0;
} LogicOutputs;

#endif
