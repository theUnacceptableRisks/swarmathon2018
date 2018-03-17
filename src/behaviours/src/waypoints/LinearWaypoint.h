#ifndef linearwaypoint_h
#define linearwaypoint_h

#include "Waypoint.h"
#include "../LinearPID.h"

typedef struct linear_params
{
    double distance;
    int max_output;
} LinearParams;

class LinearWaypoint : public Waypoint
{
    public:
        LinearWaypoint( LogicInputs *i, LinearParams lp ) : Waypoint( i ), l_params(lp), original_x(i->raw_odom.x), original_y(i->raw_odom.y)
        {
            linear_pid = LinearPID( WaypointUtilities::getDistancePIDParams() );
        }
        virtual void run();
    private:
        LinearPID linear_pid;
        LinearParams l_params;
        double original_x;
        /* for sim */
        double original_y;
};

#endif
