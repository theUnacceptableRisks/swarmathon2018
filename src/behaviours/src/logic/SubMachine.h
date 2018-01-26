#ifndef submachine_h
#define submachine_h

#include "../state_machine/StateMachine.h"
#include "../waypoints/Waypoint.h"
#include "LogicTypes.h"

class SubMachine : public StateMachine
{
    public:
        SubMachine( IOTable *io ) : StateMachine(), inputs(io->inputs), outputs(io->outputs) {}
    protected:
        virtual void runAddonsPre();
        void nextWaypoint();
        void clearWaypoints();

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
};

#endif
