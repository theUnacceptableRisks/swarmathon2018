#ifndef pickupstate_h
#define pickupstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"
#include "LogicState.h"
#include "pickup/PickUpMachine.h"

class PickUpState : public LogicState
{
    public:
        SearchState() : LogicState( "pickup_state" ), pickup_machine(0) {}
        ~SearchState()
        {
            if( pickup_machine )
                delete search_machine;
            search_machine = 0;
        }
        virtual bool setOwner( StateMachine *sm );
        virtual void action( void );
    private:
        PickUpMachine *pickup_machine;
};

#endif
