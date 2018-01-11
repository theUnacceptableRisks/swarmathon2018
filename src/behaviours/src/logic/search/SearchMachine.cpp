#include "SearchMachine.h"

SearchMachine::SearchMachine()
{
}

SearchMachine::SearchMachine( LogicInputs *i ) : inputs(i) {}

void SearchMachine::nextWaypoint()
{
    if( waypoints.size() != 0 )
    {
        waypoints.erase( waypoints.begin() );
    }
}

Waypoint *SearchMachine::getCurrentWaypoint()
{
    Waypoint *waypoint = 0;

    if( waypoints.size() > 0 )
       waypoint = &waypoints.at(0);

    return waypoint;
}
