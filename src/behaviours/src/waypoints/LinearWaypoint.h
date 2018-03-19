#ifndef linearwaypoint_h
#define linearwaypoint_h

#include "Waypoint.h"
#include "../Velocity.h"
#include "../LinVelPID.h"

typedef struct linear_params
{
    double distance;
    double max_velocity = 0.35;
    double min_velocity = 0.1;
    double deccel_point = 0.15;
    int max_output = 60;
    bool reverse = false;
} LinearParams;

class LinearWaypoint : public Waypoint
{
    public:
        LinearWaypoint( LogicInputs *i, LinearParams lp ) : Waypoint( i ), l_params(lp), original_x(i->raw_odom.x), original_y(i->raw_odom.y)
        {
            linear_pid = LinVelPID( WaypointUtilities::getLinearVelBasedPIDParams() );
        }
        virtual void run();
    private:
        LinVelPID linear_pid;
        LinearParams l_params;
        double original_x;
        /* for sim */
        double original_y;
};

#endif
