#include "SubMachine.h"

void SubMachine::nextWaypoint()
{
    Waypoint *waypoint = 0;
    if( waypoints.size() != 0 )
    {
        delete waypoints.front();
        waypoints.erase( waypoints.begin() );
        if( waypoints.size() != 0 )
            outputs->current_waypoint = waypoints.front();
        else
            outputs->current_waypoint = 0;
    }
}

void SubMachine::clearWaypoints()
{
    while( waypoints.size() != 0 )
        nextWaypoint();
}
