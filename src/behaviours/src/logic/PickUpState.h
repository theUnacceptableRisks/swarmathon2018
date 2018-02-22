#ifndef pickupstate_h
#define pickupstate_h

#include "../state_machine/State.h"
#include "../waypoints/ApproachTagWaypoint.h"
#include "../waypoints/LinearWaypoint.h"
#include "LogicTypes.h"

#define MAX_ATTEMPTS 20
#define CLOSE_TIME .25

typedef enum
{
    PICKUP_INIT,
    PICKUP_APPROACH,
    PICKUP_FINAL_APPROACH,
    PICKUP_CLAW_CLOSE,
    PICKUP_CLAW_UP,
    PICKUP_CONFIRM,
    PICKUP_HOVER_CLOSE,
    PICKUP_COMPLETE,
    PICKUP_FAIL
} PUState;

class PickUpState : public State
{
    public:
        PickUpState( IOTable *io ) : State( "pickup_state" ), internal_state(PICKUP_INIT), inputs(io->inputs), outputs(io->outputs) {}
        virtual void action( void );
        virtual void onEnter();
        virtual void onExit();
        virtual std::string transition();

    private:
        PUState internalTransition();
        void internalAction();
        void forceTransition( PUState transition_to );

        ApproachTagWaypoint *approach;
        LinearWaypoint *linear;

        double timer;

        LogicInputs *inputs;
        LogicOutputs *outputs;
        PUState internal_state;
        int attempts;
};

#endif
