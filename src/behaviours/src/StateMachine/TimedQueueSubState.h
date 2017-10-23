#ifndef timedqueuesubstate_h
#define timedqueuesubstate_h

#include "TimedQueueState.h"

class TimedQueueSubState : public TimedQueueState
{
    public:
        TimedQueueSubState( HighState *owner, std::string id "timed queue substate", unsigned long long &t ) :
            owner_state(state), TimedQueueState( id, t ) {}
    protected:
        HighState *owner_state;
};

#endif
