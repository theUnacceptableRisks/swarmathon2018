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

typedef enum
{
    CLOSEST,
    FARTHEST,
    LEFT_MOST,
    RIGHT_MOST
} ApproachType;

typedef struct tag_params
{
    int desired_tag = 0;

    double dist_deccel = 0.05;
    double dist_goal = 0.25;
    int dist_max_output = 10;

    double yaw_deccel = 0.1;
    double yaw_goal = 0.023;
    int yaw_max_output = 60;

    ApproachType type = CLOSEST;
    double skid_rotate_threshold = 0.05;

} TagParams;

class ApproachTagWaypoint : public Waypoint
{
    public:
        ApproachTagWaypoint( LogicInputs *i, TagParams tp ) : Waypoint( i ), t_params(tp), prev_distance(0) {}
        virtual void run();
    private:
        TagParams t_params;
        double prev_distance;
};

#endif
