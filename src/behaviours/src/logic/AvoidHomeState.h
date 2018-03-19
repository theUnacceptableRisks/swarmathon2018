#ifndef avoidhomestate_h
#define avoidhomestate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

#define SEARCH_SIZE 20.0

typedef enum
{
    AVOIDHOME_INIT,
    AVOIDHOME_DRIVE,
    AVOIDHOME_ESCAPE
} InternalAvoidHomeState;

class AvoidHomeState : public State
{
    public:
        AvoidHomeState( IOTable *io ) : State( "avoidhome_state" ), inputs(io->inputs), outputs(io->outputs), internal_state( AVOIDHOME_INIT ) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        double initialTime = 0;
        double angleToGoal = 0;
        double wheelRatio = 1;
        double getNearestUS ();
        InternalAvoidHomeState internalTransition();
        void internalAction();
        void forceTransition( InternalAvoidHomeState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        InternalAvoidHomeState internal_state;

};

#endif
