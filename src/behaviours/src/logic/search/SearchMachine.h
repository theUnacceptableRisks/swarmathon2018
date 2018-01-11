#ifndef searchmachine_h
#define searchmachine_h

#include "../LogicMachine.h"

class SearchMachine : public LogicMachine
{
    friend class SearchInit;
    friend class SearchDrive;
    public:
        SearchMachine( LogicInputs *i );
    private:
        void nextWaypoint();
        std::vector<Waypoint> waypoints;
};

#endif
