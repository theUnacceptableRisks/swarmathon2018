#ifndef avoid_h
#define avoid_h

#include "../state_machine/State.h"
#include "LogicMachine.h"
#include "../waypoints/LinearWaypoint.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "../waypoints/SimpleWaypoint.h"
#include "../TagUtilities.h"

#define MAX_EXIT_ATTEMPTS 7

#define ROTATION_SPEED 65

typedef enum
{
    AVOID_INIT,
    AVOID_ROTATE,
    AVOID_DRIVE,
    AVOID_ATTEMPT_EXIT,
    AVOID_EXIT_FAILURE,
    AVOID_EXIT_SUCCESS
} ASState;

class Avoid : public State
{
    public:
        Avoid( IOTable *io ) : State( "avoid_state" ), inputs(io->inputs), outputs(io->outputs), internal_state(AVOID_INIT), attempts(0) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();

    private:
        LogicInputs *inputs;
        LogicOutputs *outputs;
        ASState internalTransition();
        void internalAction();
        void forceTransition( ASState transition_to );

        LinearWaypoint *drive;
        RawOutputWaypoint *rotate;
        SimpleWaypoint *entrance_goal;
        ASState internal_state;
        std::string previous_state;
        int attempts;
        double timer;
};

#endif
