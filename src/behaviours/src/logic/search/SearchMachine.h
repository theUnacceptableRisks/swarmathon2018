#ifndef searchmachine_h
#define searchmachine_h

#include "../LogicMachine.h"

class SearchMachine : public StateMachine
{
    friend class SearchInit;
    friend class SearchDrive;
    public:
        SearchMachine( LogicInputs *i );
        Waypoint *getCurrentWaypoint();
    private:
        void nextWaypoint();
        std::vector<Waypoint> waypoints;
};

#endif
