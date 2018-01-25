#ifndef submachines_h
#define submachines_h

#include "../state_machines/StateMachine.h"
#include "LogicTypes.h"

class SubMachine : public StateMachine
{
    public:
        SubMachine( IOTable *io ) : StateMachine(), inputs(io->inputs), outputs(io->outputs) {}
    protected:
        void nextWaypoint();
        void clearWaypoints();

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
};

#endif
