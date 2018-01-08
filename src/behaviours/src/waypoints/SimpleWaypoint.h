#ifndef simplewaypoint_h
#define simplewaypoint_h

#include "Waypoint.h"
#include "WaypointUtilities.h"

//SimpleWaypointStates seperate .cpp/.h

class SimpleWaypoint : public Waypoint
{
    friend class SimpleWaypointState;
    friend class SimpleWaypointRotate;
    friend class SimpleWaypointSkid;
    friend class SimpleWaypointArrived;
    public:
        SimpleWaypoint( WaypointUtilities::DrivingParams i );
    private:
        WaypointUtilities::PidPackage pids;
        WaypointUtilities::DrivingParams inputs;
};

#endif
