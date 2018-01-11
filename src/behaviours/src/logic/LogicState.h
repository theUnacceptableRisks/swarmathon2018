#ifndef logicstate_h
#define logicstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"
class LogicState : public State
{
    public:
        LogicState() : lm_owner(0) {}
        virtual bool setOwner( StateMachine *sm );
    private:
        LogicMachine *lm_owner;
};

#endif
