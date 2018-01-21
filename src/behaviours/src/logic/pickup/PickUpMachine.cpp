#include "PickUpMachine.h"

PickUpMachine::PickUpMachine()
{
}

PickUpMachine::PickUpMachine( LogicInputs *i ) : StateMachine(), inputs(i)
{
    //init/add states
}

Waypoint *PickUpMachine::getCurrentWaypoint()
{
    Waypoint *waypoint = 0;

    if( waypoints.size() > 0 )
       waypoint = waypoints.at(0);

    return waypoint;
}

Gripper::Position PickUpMachine::getCurrentGripperPosition()
{
    return gripper_position;
}

void PickUpMachine::nextWaypoint()
{
    if( waypoints.size() != 0 )
    {
        delete waypoints.front();
        waypoints.erase( waypoints.begin() );
    }
}

void PickUpMachine::clearWaypoints()
{
    while( waypoints.size() != 0 )
        nextWaypoint();
}
