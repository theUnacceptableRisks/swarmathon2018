#ifndef approachtagwaypoint_h
#define approachtagwaypoint_h

#include "../Tag.h"
#include "../TagUtilities.h"
#include "../logic/LogicTypes.h"
#include "Waypoint.h"


class ApproachTagWaypoint : public Waypoint
{
    public:
        ApproachTagWaypoint( LogicInputs *i );
    private:
        WaypointUtilties::PidPackage pids;
        ApproachTagParams inputs;
};

#endif

