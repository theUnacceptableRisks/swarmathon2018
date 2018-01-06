#include "../state_machine/StateMachine.h"

class LogicState : public State
{
    public:
        LogicState() {}
        virtual bool setOwner( StateMachine *sm );
    private:
        LogicMachine *lm_owner;
};
