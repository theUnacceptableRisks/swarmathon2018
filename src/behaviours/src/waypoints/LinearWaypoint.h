#ifndef linearwaypoint_h
#define linearwaypoint_h

#include "Waypoint.h"

typedef struct linear_params
{
    double distance;
    double deccel_point;
    int max_vel;
} LinearParams;

class LinearWaypoint : public Waypoint
{
    public:
        LinearWaypoint( LogicInputs *i, LinearParams lp ) : Waypoint( i ), l_params(lp)
        {
            d_params.goal_x = i->raw_odom.x;
            d_params.goal_y = i->raw_odom.y;
            d_params.current_x = &i->raw_odom.x;
            d_params.current_y = &i->raw_odom.y;
        }
        virtual void run();
    private:
        WaypointUtilities::DrivingParams d_params;
        LinearParams l_params;
        double distance;
};

#endif
