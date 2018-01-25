#include "PickUpState.h"

void PickUpState::action()
{
    pickup_machine->run();
    //TODO: else messaging
    if( owner )
    {
        LogicMachine *lm_owner = std::dynamic_cast<LogicMachine *>( owner );
        if( lm_owner )
        {
            lm_owner->outputs->current_waypoint = pickup_machine->getCurrentWaypoint();
            lm_owner->outputs->current_gripper_position = pickup_machine->getCurrentGripperPosition();
        }
    }

}
