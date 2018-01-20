#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "Waypoint.h"
#include "WaypointUtilities.h"
#include "../PID.h"

//SimpleWaypointStates seperate .cpp/.h

typedef struct simple_waypoint_supplemental_params
{
    double skid_steer_threshold = 0.4;
    double final_approach_threshold = 0.2;
    double *odom_x = 0;
    double *odom_y = 0;
} SimpleWaypointSupplementalInputs;


class SimpleWaypoint : public Waypoint
{
    friend class SimpleWaypointState;
    friend class SimpleWaypointRotate;
    friend class SimpleWaypointSkid;
    friend class SimpleWaypointFinalApproach;
    friend class SimpleWaypointArrived;
    public:
        SimpleWaypoint( WaypointUtilities::DrivingParams i, SimpleWaypointSupplementalInputs si );
    private:
        WaypointUtilities::PidPackage pids;
        WaypointUtilities::DrivingParams inputs;
        SimpleWaypointSupplementalInputs supplemental_inputs;
        double approach_vel;
        double approach_x;
        double approach_y;
 };

#endif
