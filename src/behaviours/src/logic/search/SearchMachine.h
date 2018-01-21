#ifndef searchmachine_h
#define searchmachine_h

#include "../LogicMachine.h"

class SearchMachine : public StateMachine
{
    friend class SearchStateBase;
    friend class SearchInit;
    friend class SearchDrive;
    public:
        SearchMachine();
        SearchMachine( LogicInputs *i );
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
