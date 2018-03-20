#ifndef dropoffstate_h
#define dropoffstate_h

#include "../state_machine/State.h"
#include "../waypoints/ApproachHome.h"
#include "../waypoints/LinearWaypoint.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "../TagExaminer.h"
#include "LogicTypes.h"

#define DROPOFF_MAX_ATTEMPTS 20
#define DROPOFF_TIME 15
/* in sim */
//#define ROTATION_SPEED 30
/* in irl */
#define ROTATION_SPEED 65
//#define YAW_LOW_RANGE 2.1
//#define YAW_HIGH_RANGE 2.4

typedef enum
{
    DROPOFF_INIT,
    DROPOFF_APPROACH,
    DROPOFF_ADJUST,
    DROPOFF_WIGGLE_LEFT,
    DROPOFF_WIGGLE_RIGHT,
    DROPOFF_ENTER,
    DROPOFF_EXIT_BACKUP,
    DROPOFF_EXIT,
    DROPOFF_FAIL,
    DROPOFF_COMPLETE
} DOState;

class DropOffState : public State
{
    public:
        DropOffState( IOTable *io ) : State( "dropoff_state" ), internal_state(DROPOFF_INIT), inputs(io->inputs), outputs(io->outputs), attempts(0), yaw_average(0), orientation(TagExaminer::INIT) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();

    private:
        DOState internalTransition();
        void internalAction();
        void forceTransition( DOState transition_to );

        ApproachHome *approach;
        RawOutputWaypoint *alignment;
        LinearWaypoint *enter;
        LinearWaypoint *exit;

        LogicInputs *inputs;
        LogicOutputs *outputs;
        DOState internal_state;

        double timer;
        int attempts;
        double yaw_average;

        TagExaminer::Turns orientation;
        bool adjusted;

};

#endif
