#include "SearchState.h"

void SearchState::action()
{
    search_machine->run();
    //TODO: else messaging
    if( lm_owner )
    {
        lm_owner->current_waypoint = search_machine->getCurrentWaypoint();
        lm_owner->current_gripper_position = search_machine->getCurrentGripperPosition();
    }
}

bool SearchState::setOwner( StateMachine *sm )
{
    bool success = false;

    if( !owner && !lm_owner )
    {
        owner = sm;
        lm_owner = dynamic_cast<LogicMachine *>(sm);
        search_machine = new SearchMachine( lm_owner->inputs );
        success = true;
    }

    return success;
}
