#ifndef logictypes_h
#define logictypes_h

#include <vector>
#include <geometry_msgs/Pose2D.h>
#include "../Tag.h"
#include "../TagUtilities.h"
#include "../Gripper.h"
#include "../MotorController.h"
#include "../TagExaminer.h"
#include "../Cube.h"

class Waypoint;

typedef struct calibration_nums
{
    int motor_min = 12;
    int rotational_min = 15;
} CalibNums;

struct roverInfo {
    int id;
    string name;
    float x;
    float y;
    float sonar_left;
    float sonar_right;
    float sonar_center;
    string state;
    int number_of_cubes;
    int number_of_base_tags;

    bool operator < ( const roverInfo& sec ) const
    {
        return ( name < sec.name );
    }
};

typedef struct logic_inputs
{
    geometry_msgs::Pose2D	raw_odom;
    geometry_msgs::Pose2D	odom_accel;
    geometry_msgs::Pose2D	odom_accel_gps;
    std::vector<Tag> 		tags;
    std::vector<Cube>           cubes;
    double          goal_x;
    double          goal_y;
    bool            goalInObst = false;
    bool            rotationFlag = false;
    double          initialAvoidAngle;
    double          initialAvoidX;
    double          initialAvoidY;
    std::string          prevState;
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
    TagExaminer                 examiner;
    std::vector<roverInfo>	infoVector;
    std::string			rover_name;
} LogicInputs;

typedef struct logic_outputs
{
    Gripper::Position gripper_position = Gripper::HOVER_OPEN;
    Waypoint *current_waypoint = 0;
    double offset_x = 0.;
    double offset_y = 0.;
} LogicOutputs;

typedef struct io_table
{
    LogicInputs *inputs;
    LogicOutputs *outputs;
} IOTable;

bool shouldAvoidCube( LogicInputs *inputs );

#endif
