#include "PickUpState.h"

void PickUpState::action()
{
    pickup_machine->run();
    //TODO: else messaging
    if( lm_owner )
    {
        lm_owner->current_waypoint = pickup_machine->getCurrentWaypoint();
    }

}

bool PickUpState::setOwner( StateMachine *sm )
{
    bool success = false;

    if( !owner && !lm_owner )
    {
        owner = sm;
        lm_owner = dynamic_cast<LogicMachine *>(sm);
        pickup_machine = new PickUpMachine( lm_owner->inputs );
        success = true;
    }

    return success;
}
