#ifndef initstate_h
#define initstate_h

#include "../state_machine/State.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "../TagUtilities.h"
#include "LogicTypes.h"

#define GIVE_UP_TIME 10
#define DISTANCE_TO_CENTER .508
#define PWM_OUTPUT 35

typedef enum
{
    INIT_START,
    INIT_APPROACH,
    INIT_CALIBRATE,
    INIT_BACKUP,
    INIT_COMPLETE,
    INIT_FAIL
} IState;

class InitState : public State
{
    public:
        InitState( IOTable *io ) : State( "init_state" ), internal_state(INIT_START), inputs(io->inputs), outputs(io->outputs), calibration_complete(false) {}
        virtual void action( void );
        virtual std::string transition();

    private:
        IState internalTransition();
        void internalAction();
        void forceTransition( IState transition_to );

        IState internal_state;
        RawOutputWaypoint *drive;
        bool calibration_complete;
        double start_time;

        LogicInputs *inputs;
        LogicOutputs *outputs;
};


#endif
