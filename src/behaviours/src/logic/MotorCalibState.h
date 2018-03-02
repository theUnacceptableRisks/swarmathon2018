#ifndef motorcalibstate_h
#define motorcalibstate_h

#include "../state_machine/State.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "LogicMachine.h"

typedef enum
{
    MOTORCALIB_INIT,
    MOTORCALIB_DRIVE,
    MOTORCALIB_CHECK,
    MOTORCALIB_COMPLETE
} MCState;

class MotorCalibState : public State
{
    public:
        MotorCalibState( IOTable *io ) : State( "motorcalib_state" ), inputs(io->inputs), outputs(io->outputs), internal_state(MOTORCALIB_INIT) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string, next_state );
        virtual std::string transition();
    private:
        MCState internalTransition();
        void internalAction();
        void forceTransition( MCState transition_to );

        RawOutputWaypoint *waypoint;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        MCState internal_state;

        int current_PWM;
};

#endif
