#ifndef rotationalcalibstate_h
#define rotationalcalibstate_h

#include "../state_machine/State.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "../TagUtilities.h"
#include "LogicMachine.h"

#define MIN_ROT_DISTANCE 0.01
#define CALIB_ROT_DURATION 1

typedef enum
{
    ROTATIONALCALIB_INIT,
    ROTATIONALCALIB_APPROACH_HOME,
    ROTATIONALCALIB_ATTEMPT_ROTATION,
    ROTATIONALCALIB_CHECK,
    ROTATIONALCALIB_COMPLETE
} RCState;

class RotationalCalibState : public State
{
    public:
        RotationalCalibState( IOTable *io ) : State( "rotationalcalib_state" ), inputs(io->inputs), outputs(io->outputs), internal_state(ROTATIONALCALIB_INIT), current_PWM(0), prev_distance(0), rot_direction(0), found_optimal(false) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        RCState internalTransition();
        void internalAction();
        void forceTransition( RCState transition_to );

        RawOutputWaypoint *waypoint;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        RCState internal_state;

        double prev_distance;
        int rot_direction;
        bool found_optimal;
        int current_PWM;
};

#endif

