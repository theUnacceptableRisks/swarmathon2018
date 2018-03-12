#ifndef linearwaypoint_h
#define linearwaypoint_h

#include "Waypoint.h"

typedef struct linear_params
{
    double distance;
    int max_output;
    bool reverse = false;
} LinearParams;

class LinearWaypoint : public Waypoint
{
    public:
        LinearWaypoint( LogicInputs *i, LinearParams lp ) : Waypoint( i ), l_params(lp), original_x(i->raw_odom.x)
        {
            linear_pid = PID( WaypointUtilities::getDistancePIDParams() );
        }
        virtual void run();
    private:
        PID linear_pid;
        LinearParams l_params;
        double original_x;
};

#endif
