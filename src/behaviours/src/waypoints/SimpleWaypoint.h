#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "Waypoint.h"
#include "../PID.h"

//SimpleWaypointStates seperate .cpp/.h

typedef struct simple_params
{
    double skid_steer_threshold = M_PI / 6;
    double final_approach_threshold = 0.2;
    double max_vel = 40;
    double goal_x = 0;
    double goal_y = 0;
} SimpleParams;


class SimpleWaypoint : public Waypoint
{
    friend class SimpleWaypointState;
    friend class SimpleWaypointRotate;
    friend class SimpleWaypointSkid;
    friend class SimpleWaypointFinalApproach;
    friend class SimpleWaypointArrived;
    public:
        SimpleWaypoint( LogicInputs *i, SimpleParams sp );
    private:
        SimpleParams simple_params;
        WaypointUtilities::DrivingParams driving_params;
        WaypointUtilities::DrivingParams secondary_driving_params;
        double approach_vel;
 };

#endif
