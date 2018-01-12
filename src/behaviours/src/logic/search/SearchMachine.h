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
    private:
        LogicInputs *inputs;
        void nextWaypoint();
        std::vector<Waypoint*> waypoints;
};

#endif
