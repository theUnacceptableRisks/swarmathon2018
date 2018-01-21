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
    public:
        LogicMachine( LogicInputs *i );
        Waypoint *getCurrentWaypoint() { return current_waypoint; }
        Gripper::gripper_position getCurrentGripperPosition() { return current_gripper_position; }
    private:
        Waypoint *current_waypoint;
        Gripper::gripper_position current_gripper_position;
        LogicInputs *inputs;
};

#endif
