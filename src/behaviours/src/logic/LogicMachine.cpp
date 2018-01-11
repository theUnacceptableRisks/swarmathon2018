#include "LogicMachine.h"
#include "SearchState.h"

LogicMachine::LogicMachine( LogicInputs *i ) : inputs(i), current_waypoint(0)
{
    addState( "search_state", new SearchState() );
}
