#include <iostream>
#include "ReturnState.h"
#include "../TagUtilities.h"

ReturnState::ReturnState( IOTable *io ) : State( "return_state" ), return_machine(ReturnMachine( io ))
{

}

void ReturnState::action()
{
    return_machine.run();
}

std::string ReturnState::transition()
{
    std::string transition_to = getIdentifier();

    LogicMachine *lm = dynamic_cast<LogicMachine *> (owner);
    if( lm )
    {
        if( TagUtilities::hasTag( &lm->inputs->tags,  256) )
            transition_to = "search_state";
    }
    return transition_to;
}
