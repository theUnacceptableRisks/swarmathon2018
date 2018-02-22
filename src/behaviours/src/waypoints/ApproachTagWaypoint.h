#ifndef approachtagwaypoint_h
#define approachtagwaypoint_h

#include "../Tag.h"
#include "../TagUtilities.h"
#include "../logic/LogicTypes.h"
#include "Waypoint.h"
#include "WaypointUtilities.h"

/*****************
 * State Machine *
 *****************/

#define RATE_OF_CHANGE_MAX 0.02
#define MAX_DISTANCE_FOR_ARRIVAL 0.23

class ApproachTagWaypoint : public Waypoint
{
    public:
        ApproachTagWaypoint( LogicInputs *i, int dt, double dd ) : Waypoint( i ), desired_tag_id(dt), desired_distance(dd) {}
        virtual void run();
    private:
        double desired_distance;
        int desired_tag_id;
};

#endif
