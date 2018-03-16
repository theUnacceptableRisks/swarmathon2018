#ifndef oliverpickupstate_h
#define oliverpickupstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

#define SEARCH_SIZE 20.0

typedef enum
{
    OLIVERPICKUP_INIT,
    OLIVERPICKUP_DRIVE
} InternalOliverPickUpState;

class OliverPickUpState : public State
{
    public:
        OliverPickUpState( IOTable *io ) : State( "oliverpickup_state" ), inputs(io->inputs), outputs(io->outputs), internal_state( OLIVERPICKUP_INIT ) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        double damper = 1;
        double angleToGoal = 0;
        double wheelRatio = 1;
        std::string previousState = "";
        double initialTheta = 0;
        double getNearestUS ();
        InternalOliverPickUpState internalTransition();
        void internalAction();
        void forceTransition( InternalOliverPickUpState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        InternalOliverPickUpState internal_state;

};

#endif
