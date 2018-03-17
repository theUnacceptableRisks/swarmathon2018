#ifndef initstate_h
#define initstate_h

#include "../state_machine/State.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "LogicTypes.h"

#define GIVE_UP_TIME 5
#define DISTANCE_TO_CENTER = .508
#define PWM_OUTPUT 25

typedef enum
{
    INIT_APPROACH,
    INIT_CALIBRATE,
    INIT_COMPLETE,
    INIT_FAIL
} IState;

class InitState : public State
{
    public:
        InitState( IOTable *io ) : State( "init_state" ), internal_state(INIT_APPROACH), inputs(io->inputs), outputs(io->outputs)
        {
            RawOutputParams params;

            params.left_output = PWM_OUTPUT;
            params.right_output = PWM_OUTPUT;
            params.duration = 5;

            drive = new RawOutputWaypoint( io->inputs, params );
        }
        virtual void action( void );
        virtual std::string transition();

    private:
        IState internalTransition();
        void internalAction();
        void forceTransition( IState transition_to );

        RawOutputWaypoint *drive;

        LogicInputs *inputs;
        LogicOutputs *outputs;
};


#endif
