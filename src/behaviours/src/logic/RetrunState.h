#ifndef returnstate_h
#define returnstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"
#include "return/ReturnMachine.h"

class ReturnState : public State
{
    public:
        ReturnState( IOTable *io );
        virtual void action( void );
        virtual std::string transition( void );
    private:
        ReturnMachine return_machine;
};

#endif
