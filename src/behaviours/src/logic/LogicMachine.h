#ifndef logicmachine_h
#define logicmachine_h

#include <vector>
#include <geometry_msgs/Pose2D.h>

#include "../state_machine/StateMachine.h"
#include "../waypoints/Waypoint.h"
#include "../Gripper.h"
#include "../Tag.h"

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
} LogicInputs;

class LogicMachine : public StateMachine
{
    /* need to write these  inits */
    friend class InitState;
    friend class SearchState;
    friend class PickUpState;
    friend class FindHomeState;
    friend class DropOffState;
    friend class ObstacleAvoidanceState;
    public:
        LogicMachine( LogicInputs *i );
        Waypoint *getCurrentWaypoint() { return current_waypoint; }
        Gripper::gripper_position getCurrentGripperPosition() { return current_gripper_position; }
    private:
        Waypoint *current_waypoint;
        Gripper::gripper_position current_gripper_position;
        LogicInputs *inputs;
};

#endif
