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

typedef enum
{
   AT_CENTER,
   AT_APPROACH,
   AT_ARRIVED,
   AT_FAILED
} ATState;

class ApproachTagWaypoint : public Waypoint
{
    public:
        ApproachTagWaypoint( LogicInputs *i, int dt );
        virtual void run();
    private:
        ATState internalTransition();
        void internalAction();
        void forceTransition( ATState transition_to );

        ATState internal_state;
        int validation_counter;

        double prev_dist_to_tag;
        int desired_tag_id;
};

#endif
