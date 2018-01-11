#include "SearchState.h"

void SearchState::action()
{
    search_machine.run();
    //TODO: else messaging
    if( lm_owner )
    {
        lm_owner->current_waypoint = search_machine.getCurrentWaypoint();
    }
}

bool SearchState::setOwner( StateMachine *sm )
{
    bool success = false;

    if( !owner && !lm_owner )
    {
        owner = sm;
        lm_owner = (LogicMachine *)sm;
        search_machine = SearchMachine( lm_owner->inputs );
        success = true;
    }

    return success;
}
