#ifndef obstavoid_h
#define obstavoid_h

#include "../state_machine/State.h"
#include "LogicMachine.h"


typedef enum
{
    AVOID_INIT,
    AVOID_FOLLOW,
    AVOID_LOST
} AvoidState;

class ObstAvoidState : public State
{
    public:
        ObstAvoidState( IOTable *io ) : State( "obstavoid_state" ), inputs(io->inputs), outputs(io->outputs), internal_state(AVOID_INIT) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();

    private:
        AvoidState internalTransition();
        void internalAction();
        void forceTransition( FHState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        FHState internal_state;
};

#endif
