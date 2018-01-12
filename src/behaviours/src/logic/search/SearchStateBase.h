#ifndef searchstatebase_h
#define searchstatebase_h

#include "../../state_machine/State.h"
#include "../../waypoints/SimpleWaypoint.h"
#include "SearchMachine.h"

class SearchStateBase : public State
{
    public:
        SearchStateBase( std::string identifier ) : State( identifier ), ssm_owner(0) {}
        virtual bool setOwner( StateMachine *sm );
    protected:
        SearchMachine *ssm_owner;
};

#endif
