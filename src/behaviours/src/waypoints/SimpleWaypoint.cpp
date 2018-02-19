#include "SimpleWaypoint.h"
#include "SimpleWaypointStates.h"

void SimpleWaypoint::run()
{
    forceTransition( inernalTransition() );
    internalAction();
}

SWState SimpleWaypoint::internalTransition()
{
    SWState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
    }

    return transition_to;
}

void SimpleWaypoint::internalAction()
{
    switch( internal_state )
    {
        default: break;
    }
}

void SimpleWaypoint::forceTransition( SWState transition_to )
{

}
