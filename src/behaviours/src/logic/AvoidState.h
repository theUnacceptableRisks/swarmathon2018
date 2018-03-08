#ifndef avoidstate_h
#define avoidstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

#define SEARCH_SIZE 20.0

typedef enum
{
    AVOID_INIT,
    AVOID_DRIVE
} InternalState;

class AvoidState : public State
{
    public:
        AvoidState( IOTable *io ) : State( "avoid_state" ), inputs(io->inputs), outputs(io->outputs), internal_state( AVOID_INIT ) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        double wheelRatio = 1;
        double getNearestUS ();
        InternalState internalTransition();
        void internalAction();
        void forceTransition( InternalState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        InternalState internal_state;

};

#endif
