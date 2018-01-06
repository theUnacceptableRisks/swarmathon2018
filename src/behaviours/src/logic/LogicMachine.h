#include "../state_machine/StateMachine.h"
#include "../waypoints/Waypoint.h"

class LogicMachine : public StateMachine
{
    friend class StateSearch;
    public:
        LogicMachine() : current_waypoint(0) {}
        Waypoint *getCurrentWaypoint() { return current_waypoint; }
    private:
        Waypoint *current_waypoint;
};
