#ifndef linearwaypoint_h
#define linearwaypoint_h

#include "Waypoint.h"

typedef struct linear_params
{
    double distance;
    double deccel_point;
    int max_vel;
    bool reverse = false;
} LinearParams;

class LinearWaypoint : public Waypoint
{
    public:
        LinearWaypoint( LogicInputs *i, LinearParams lp ) : Waypoint( i ), l_params(lp), original_x(i->raw_odom.x) {}
        virtual void run();
    private:
        LinearParams l_params;
        double original_x;
};

#endif
