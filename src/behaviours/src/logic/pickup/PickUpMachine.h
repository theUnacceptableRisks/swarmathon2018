#ifndef pickupmachine_h
#define pickupmachine_h

#include "../LogicMachine.h"

class PickUpMachine : public StateMachine
{
    public:
        PickUpMachine();
        PickUpMachine( LogicInputs *i );
        Waypoint *getCurrentWaypoint();
        Gripper::Position getCurrentGripperPosition();
    private:
        LogicInputs *inputs;
        void nextWaypoint();
        void clearWaypoints();

        std::vector<Waypoint*> waypoints;
        Gripper::Position gripper_position;
};

#endif
