#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "Waypoint.h"
#include "../inputs/InputLocation.h"
#include "WaypointUtilities.h"

//SimpleWaypointStates seperate .cpp/.h

class SimpleWaypoint : public Waypoint
{
    friend class SimpleWaypointState;
    friend class SimpleWaypointRotate;
    friend class SimpleWaypointSkid;
    friend class SimpleWaypointArrived;
    public:
        SimpleWaypoint( DrivingParams i );
    private:
        WaypointUtilities::PidPackage pids;
        WaypointUtilities::DrivingParams inputs;
        const float goal_x;
        const float goal_y;
};

#endif
