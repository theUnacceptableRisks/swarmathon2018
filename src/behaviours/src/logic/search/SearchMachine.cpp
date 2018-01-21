#include "SearchMachine.h"
#include "SearchInit.h"
#include "SearchDrive.h"

SearchMachine::SearchMachine()
{
}

SearchMachine::SearchMachine( LogicInputs *i ) : StateMachine(), inputs(i), gripper_position(Gripper::HOVER_OPEN)
{
    SearchInit *init = new SearchInit();
    SearchDrive *drive = new SearchDrive();

    addState( init->getIdentifier(), (State *)init );
    addState( drive->getIdentifier(), (State *)drive );
}

Waypoint *SearchMachine::getCurrentWaypoint()
{
    Waypoint *waypoint = 0;

    if( waypoints.size() > 0 )
       waypoint = waypoints.at(0);

    return waypoint;
}

Gripper::Position SearchMachine::getCurrentGripperPosition()
{
    return gripper_position;
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

void SearchMachine::clearWaypoints()
{
    while( waypoints.size() != 0 )
        nextWaypoint();
}
