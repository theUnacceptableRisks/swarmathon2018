#ifndef avoidcubestate_h
#define avoidcubestate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

#define SEARCH_SIZE 20.0

typedef enum
{
    AVOIDCUBE_INIT,
    AVOIDCUBE_DRIVE,
    AVOIDCUBE_ESCAPE
} InternalAvoidCubeState;

class AvoidCubeState : public State
{
    public:
        AvoidCubeState( IOTable *io ) : State( "avoidcube_state" ), inputs(io->inputs), outputs(io->outputs), internal_state( AVOIDCUBE_INIT ) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        double waypointTimer = 0;
        double initialTime = 0;
        double angleToGoal = 0;
        double wheelRatio = 1;
        double initialTheta = 0;
        double getNearestUS ();
        InternalAvoidCubeState internalTransition();
        void internalAction();
        void forceTransition( InternalAvoidCubeState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        InternalAvoidCubeState internal_state;

};

#endif
