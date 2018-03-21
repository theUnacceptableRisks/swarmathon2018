#ifndef findhome_h
#define findhome_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

#define MAX_RINGS 7

typedef enum
{
    FINDHOME_INIT,
    FINDHOME_GOHOME,
    FINDHOME_LOST,
    FINDHOME_COMPLETE,
    FINDHOME_RESET
} FHState;

class FindHomeState : public State
{
    public:
        FindHomeState( IOTable *io ) : State( "findhome_state" ), inputs(io->inputs), outputs(io->outputs), internal_state(FINDHOME_INIT) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();

    private:
        FHState internalTransition();
        void internalAction();
        void forceTransition( FHState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        FHState internal_state;
};

#endif
