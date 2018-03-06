#ifndef dropoffstate_h
#define dropoffstate_h

#include "../state_machine/State.h"
#include "../waypoints/ApproachTagWaypoint.h"
#include "../waypoints/LinearWaypoint.h"
#include "../waypoints/RawOutputWaypoint.h"
#include "LogicTypes.h"

typedef enum
{
    DROPOFF_INIT,
    DROPOFF_ADJUST,
    DROPOFF_WIGGLE_LEFT,
    DROPOFF_WIGGLE_RIGHT,
    DROPOFF_ENTER,
    DROPOFF_EXIT_BACKUP,
    DROPOFF_EXIT,
    DROPOFF_COMPLETE
} DOState;

class DropOffState : public State
{
    public:
        DropOffState( IOTable *io ) : State( "dropoff_state" ), internal_state(DROPOFF_INIT), inputs(io->inputs), outputs(io->outputs) {}
    private:
};

#endif
