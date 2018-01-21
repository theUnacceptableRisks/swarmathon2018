#include "LogicMachine.h"
#include "SearchState.h"

LogicMachine::LogicMachine( LogicInputs *i ) : StateMachine(), inputs(i), current_waypoint(0),
                                               current_gripper_position(Gripper::HOVER_OPEN)
{
//    addState( "search_state", new SearchState() );
}
