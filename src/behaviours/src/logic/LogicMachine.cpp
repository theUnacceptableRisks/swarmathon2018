#include "LogicMachine.h"
#include "SearchState.h"

LogicMachine::LogicMachine( IOTable *io ) : StateMachine(), inputs(io->inputs), outputs(io->outputs)
{
    addState( "search_state", new SearchState( io ) );
}
