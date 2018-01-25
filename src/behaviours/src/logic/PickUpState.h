#ifndef pickupstate_h
#define pickupstate_h

#include "../state_machine/State.h"
#include "LogicMachine.h"
#include "LogicState.h"
#include "pickup/PickUpMachine.h"

class PickUpState : public State
{
    public:
        PickUpState() : LogicState( "pickup_state" ), pickup_machine(0) {}
        virtual void action( void );
};

#endif
