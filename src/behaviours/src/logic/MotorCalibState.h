#ifndef motorcalibstate_h
#define motorcalibstate_h

#include "../state_machine/State.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "LogicMachine.h"

#define MIN_DISTANCE 0.01
#define CALIB_DRIVE_DURATION 1

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
        MotorCalibState( IOTable *io ) : State( "motorcalib_state" ), inputs(io->inputs), outputs(io->outputs), internal_state(MOTORCALIB_INIT), current_PWM(0), found_optimal(false) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        MCState internalTransition();
        void internalAction();
        void forceTransition( MCState transition_to );

        RawOutputWaypoint *waypoint;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        MCState internal_state;

        double prev_x;
        bool found_optimal;
        int current_PWM;
};

#endif
