#ifndef searchstate_h
#define searchstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"

#define SEARCH_SIZE 20.0

typedef enum
{
    SEARCHSTATE_INIT,
    SEARCHSTATE_DRIVE
} SSState;

class SearchState : public State
{
    public:
        SearchState( IOTable *io ) : State( "search_state" ), internal_state( SEARCHSTATE_INIT ) {}
        virtual void action( void );
        virtual void onEnter( std::string prev_state );
        virtual void onExit( std::string next_state );
        virtual std::string transition();
    private:
        SSState internalTransition();
        void internalAction();
        void forceTransition( SSState transition_to );

        std::vector<Waypoint *> waypoints;
        LogicInputs *inputs;
        LogicOutputs *outputs;
        SSState internal_state;

};

#endif
