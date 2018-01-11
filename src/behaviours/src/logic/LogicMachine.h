#ifndef logicmachine_h
#define logicmachine_h

#include "../state_machine/StateMachine.h"
#include "../waypoints/Waypoint.h"
#include <geometry_msgs/Pose2D.h>
#include "../Tag.h"
#include <vector>

typedef struct logic_inputs
{
    geometry_msgs::Pose2D	raw_odom;
    geometry_msgs::Pose2D	odom_accel;
    geometry_msgs::Pose2D	odom_accel_gps;
    std::vector<Tag> 		tags;
    double			us_left = 0.0;
    double			us_right = 0.0;
    double			us_center = 0.0;
    float			linear_vel_odom_accel = 0.0;
    float			linear_vel_odom_accel_gps = 0.0;
    float			angular_vel_odom_accel = 0.0;
    float			angular_vel_odom_accel_gps = 0.0;
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
    private:
        Waypoint *current_waypoint;
        LogicInputs *inputs;
};

#endif
