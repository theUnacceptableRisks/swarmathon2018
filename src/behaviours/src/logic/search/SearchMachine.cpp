#include "SearchMachine.h"

SearchMachine::SearchMachine()
{
}

SearchMachine::SearchMachine( LogicInputs *i ) : LogicMachine( i ) {}

void SearchMachine::nextWaypoint()
{
    if( waypoints.size() != 0 )
    {
        waypoints.erase( waypoints.begin() );
        current_waypoint = 0;
    }
    if( waypoint.size() != 0 )
    {
        current_waypoint = &waypoints.at(0);
    }

}

Waypoint *SearchMachine::getCurrentWaypoint()
{
    return &waypoints.at(0);
}
