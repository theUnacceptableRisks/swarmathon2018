#include <iostream>
#include "SearchState.h"
#include "../TagUtilities.h"

SearchState::SearchState( IOTable *io ) : State( "search_state" ), search_machine(SearchMachine( io ))
{

}

void SearchState::action()
{
    search_machine.run();
}

std::string SearchState::transition()
{
    std::string transition_to = getIdentifier();

    LogicMachine *lm = dynamic_cast<LogicMachine *> (owner);
    if( lm )
    {
        if( TagUtilities::hasTag( &lm->inputs->tags, 0 ) )
            transition_to = "pickup_state";
    }
    return transition_to;
}
