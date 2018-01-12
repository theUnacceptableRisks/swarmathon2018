#include "SearchMachine.h"
#include "SearchInit.h"
#include "SearchDrive.h"

SearchMachine::SearchMachine()
{
}

SearchMachine::SearchMachine( LogicInputs *i ) : StateMachine(), inputs(i)
{
    SearchInit *init = new SearchInit();
    SearchDrive *drive = new SearchDrive();

    addState( init->getIdentifier(), (State *)init );
    addState( drive->getIdentifier(), (State *)drive );
}

void SearchMachine::nextWaypoint()
{
    Waypoint *waypoint = 0;
    if( waypoints.size() != 0 )
    {
        delete waypoints.front();
        waypoints.erase( waypoints.begin() );
    }
}

Waypoint *SearchMachine::getCurrentWaypoint()
{
    Waypoint *waypoint = 0;

    if( waypoints.size() > 0 )
       waypoint = waypoints.at(0);

    return waypoint;
}
