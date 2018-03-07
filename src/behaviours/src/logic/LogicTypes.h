#ifndef logictypes_h
#define logictypes_h

#include <vector>
#include <geometry_msgs/Pose2D.h>
#include "../Tag.h"
#include "../Gripper.h"
#include "../MotorController.h"
class Waypoint;

typedef struct calibration_nums
{
    int motor_min = 12;
    int rotational_min = 15;
} CalibNums;

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
    MotorController		controller;
    CalibNums			calibration;
} LogicInputs;

typedef struct logic_outputs
{
    Gripper::Position gripper_position = Gripper::HOVER_OPEN;
    Waypoint *current_waypoint = 0;
} LogicOutputs;

typedef struct io_table
{
    LogicInputs *inputs;
    LogicOutputs *outputs;
} IOTable;

#endif
