#ifndef logicmachine_h
#define logicmachine_h

#include "../state_machine/StateMachine.h"
#include "../waypoints/Waypoint.h"
#include "../Gripper.h"
#include "LogicTypes.h"

class LogicMachine : public StateMachine
{
    /* need to write these  inits */
    friend class InitState;
    friend class SearchState;
    friend class PickUpState;
    friend class FindHomeState;
    friend class DropOffState;
    friend class ObstacleAvoidanceState;
    friend class ReturnState;
    public:
        LogicMachine( IOTable *io );
    private:
        LogicInputs *inputs;
        LogicOutputs *outputs;
};

#endif
