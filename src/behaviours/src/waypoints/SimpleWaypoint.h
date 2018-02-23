#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "Waypoint.h"

//SimpleWaypointStates seperate .cpp/.h

typedef enum
{
    SIMPLE_INIT,
    SIMPLE_ROTATE,
    SIMPLE_SKID,
    SIMPLE_ARRIVED
} SWState;

typedef struct simple_params
{
    double skid_steer_threshold = M_PI/6;
    double arrived_threshold = 0.05;
    double goal_x = 0;
    double goal_y = 0;

    int dist_max_output = 60;
    double dist_deccel = 0.2;
    double dist_goal = 0.0;

    int yaw_max_output = 80;
    double yaw_deccel = M_PI/6;
    double yaw_goal = 0.0;
} SimpleParams;


class SimpleWaypoint : public Waypoint
{
    public:
        SimpleWaypoint( LogicInputs *i, SimpleParams sp ) : Waypoint( i ), simple_params(sp), internal_state(SIMPLE_INIT)
        {
            driving_params.goal_x = simple_params.goal_x;
            driving_params.goal_y = simple_params.goal_y;
            driving_params.current_x = &inputs->odom_accel_gps.x;
            driving_params.current_y = &inputs->odom_accel_gps.y;
            driving_params.current_theta = &inputs->odom_accel_gps.theta;

        }
        virtual void run();
    private:
        SWState internalTransition();
        void internalAction();
        void forceTransition( SWState transition_to );

        WaypointUtilities::DrivingParams driving_params;
        SimpleParams simple_params;
        SWState internal_state;



 };

#endif
