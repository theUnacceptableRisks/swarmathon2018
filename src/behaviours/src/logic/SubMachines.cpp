#include "SubMachines.h"

void SubMachines::nextWaypoint()
{
    Waypoint *waypoint = 0;
    if( waypoints.size() != 0 )
    {
        delete waypoints.front();
        waypoints.erase( waypoints.begin() );
    }
}

void SubMachines::clearWaypoints()
{
    while( waypoints.size() != 0 )
        nextWaypoint();
}
