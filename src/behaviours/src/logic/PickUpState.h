#ifndef pickupstate_h
#define pickupstate_h

#include "../state_machine/State.h"
#include "LogicTypes.h"

class PickUpState : public State
{
    public:
        PickUpState( IOTable *io ) : State( "pickup_state" ) {}
        virtual void action( void );
        virtual std::string transition( void );
};

#endif
