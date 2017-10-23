#ifndef timedqueuestate_h
#define timedqueuestate_h

#include "State.h"

class TimedQueueState : public State
{
    public:
        TimedQueueState( std::string id = "timed queued state", unsigned long long &t ) : timer(t), State( id ) {}
        /*
         * Either onEnter or onExit should most likely reset any events remaining
         * in the queue. Events should be initialized with an offset based on a
         * current time. If I decide not to do this, delete these two methods.
         */
        virtual void onEnter( std::string prev_state ) {}
        virtual void onExit( std::string next_state ) {}
        /*
         * Should possibly transition out if its queue is empty, but what to?
         * The state that called it?
         * If I decide to not do this, delete this method.
         */
        virtual std::transition( void ) { return state_identifier; }
        /*
         * Action will not be a virtual function because it should handle events,
         * ie, function calls, in a single uniform manner. 
         */
        void action()
        {
        }
    private:
        //event queue
        unsigned long long &timer;
};

#endif
