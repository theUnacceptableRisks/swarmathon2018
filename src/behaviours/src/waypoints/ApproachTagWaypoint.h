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
#define MAX_DISTANCE_FOR_ARRIVAL 0.21

class ApproachTagWaypoint : public Waypoint
{
    public:
        ApproachTagWaypoint( LogicInputs *i, int dt );
        virtual void run();
    private:
        double init_timer;
        Tag current_tag;
        Tag last_tag;
        int desired_tag_id;
};

#endif
