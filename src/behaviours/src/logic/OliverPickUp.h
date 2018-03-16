#ifndef pickupstate_h
#define pickupstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

#define SEARCH_SIZE 20.0

typedef enum
{
    PICKUP_INIT,
    PICKUP_DRIVE
} InternalOliverPickupState;

class OliverPickupState : public State
{
    public:
        OliverPickupState( IOTable *io ) : State( "pickup_state" ), inputs(io->inputs), outputs(io->outputs), internal_state( PICKUP_INIT ) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        double angleToGoal = 0;
        double wheelRatio = 1;
        std::string previousState = "";
        double initialTheta = 0;
        double getNearestUS ();
        InternalOliverPickupState internalTransition();
        void internalAction();
        void forceTransition( InternalOliverPickupState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        InternalOliverPickupState internal_state;

};

#endif
