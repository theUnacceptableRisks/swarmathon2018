#include "LogicMachine.h"
#include "SearchState.h"
#include "ReturnState.h"

LogicMachine::LogicMachine( IOTable *io ) : StateMachine(), inputs(io->inputs), outputs(io->outputs)
{
    addState( "search_state", new SearchState( io ) );
    addState( "return_state", new ReturnState( io ) );
}
