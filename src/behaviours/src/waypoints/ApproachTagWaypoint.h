#ifndef approachtagwaypoint_h
#define approachtagwaypoint_h

#include "../Tag.h"
#include "../TagUtilities.h"
#include "../logic/LogicTypes.h"
#include "Waypoint.h"
#include "WaypointUtilities.h"
#include "../LinearPID.h"
#include "../LinRotPID.h"
#include "../Cube.h"

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

    double dist_goal = 0.15;
    int dist_max_output = 130;

    double yaw_goal = -0.023;
    int yaw_max_output = 60;

    double skid_rotate_threshold = 0.05;

} TagParams;

class ApproachTagWaypoint : public Waypoint
{
    public:
        ApproachTagWaypoint( LogicInputs *i, TagParams tp ) : Waypoint( i ), t_params(tp) {}
        virtual void run();
    private:
        TagParams t_params;
};

#endif
