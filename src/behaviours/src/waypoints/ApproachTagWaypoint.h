#ifndef approachtagwaypoint_h
#define approachtagwaypoint_h

#include "../Tag.h"
#include "../TagUtilities.h"
#include "Waypoint.h"

typedef struct approach_tag_params
{
    std::vector<Tag> *tags = 0.0;
    int value = 0;
} ApproachTagParams;

class ApproachTagWaypoint : public Waypoint
{
    public:
        ApproachTagWaypoint( ApproachTagParams p );
    private:
        WaypointUtilties::PidPackage pids;
        ApproachTagParams inputs;
};

#endif

