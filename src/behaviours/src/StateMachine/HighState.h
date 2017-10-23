#ifndef highstate_h
#define highstate_h

/*
 * A High State essentially is a state machine employed by a state machine.
 * Its States will be friends to the HighState as necessary so that the
 * internal state machine of the High State can control the functions of
 * the high state.
 */

#include "StateMachine.h"
#include "SubState.h"

class HighState : public State
{
    friend SubState;
    friend TimedQueueSubState;
    public:
        HighState( std::string id = "high state abstract" ) : State( id ) {}

        virtual void action()
        {
            internal_machine.run();
        }

    private:
        StateMachine internal_machine;
};

#endif
