#include "SearchState.h"
#include "../TagUtilities.h"

void SearchState::action()
{
    if( search_machine )
    {
        search_machine->run();
        //TODO: else messaging
        if( owner )
        {
            LogicMachine *lm_owner = std::dynamic_cast<LogicMachine *>( owner );
            if( lm_owner )
            {
                lm_owner->outputs->current_waypoint = search_machine->getCurrentWaypoint();
                lm_owner->outputs->current_gripper_position = search_machine->getCurrentGripperPosition();
            }
        }
    }
}

void SearchState::onEnter( std::string prev_string )
{
    if( !search_machine && owner )
    {
        LogicMachine *lm_owner = std::dynamic_cast<LogicMachine *>( owner );
        search_machine = new SearchMachine( lm_owner->inputs );
    }
}

std::string SearchState::transition()
{
    std::string transition_to = getIdentifier();

    if( lm_owner )
    {
        if( TagUtilities::hasTag( &lm_owner->inputs->tags, 0 ) )
        {
            transition_to = "pickup_state";
        }
    }

    return transition_to;
}
