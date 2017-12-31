#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "Waypoint.h"
#include "../inputs/InputLocation.h"
#include "WaypointUtilities.h"

//SimpleWaypointStates seperate .cpp/.h

struct SimpleWaypointParams
{
    InputLocation *current_position;
    IOFloat *linear_vel;
    IOFloat *angular_vel;
    float x;
    float y;
};

class SimpleWaypoint : public Waypoint
{
    friend class SimpleWaypointState;
    friend class SimpleWaypointRotate;
    friend class SimpleWaypointSkid;
    friend class SimpleWaypointArrived;
    public:
        SimpleWaypoint( struct SimpleWaypointParams params );
        bool updateDrivingParams();
    private:
        WaypointUtilities::PidPackage pids;
        WaypointUtilities::DrivingParams driving_params;
        const float goal_x;
        const float goal_y;
};

#endif
