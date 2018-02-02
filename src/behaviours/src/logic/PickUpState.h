#ifndef pickupstate_h
#define pickupstate_h

#include "../state_machine/State.h"
#include "LogicTypes.h"
#include "pickup/PickUpMachine.h"

class PickUpState : public State
{
    public:
        PickUpState( IOTable *io ) : State( "pickup_state" ), pickup_machine(PickUpMachine( io )) {}
        virtual void action( void );
    private:
        PickUpMachine pickup_machine;
};

#endif
