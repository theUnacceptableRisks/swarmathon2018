#include "InitState.h"

void InitState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

std::string InitState::transition()
{
    std::string transition_to = getIdentifier();

    switch( internal_state )
    {
        default:break;
        case INIT_COMPLETE:
            transition_to = "search_state";
            break;
        case INIT_FAIL:
            transition_to = "findhome_state";
            break;
    }
}

IState InitState::internalTransition()
{
    IState transition_to = internal_state;
    switch( internal_state )
    {
        default:break;
    }

    return transition_to;
}

void InitState::internalAction()
{
    switch( internal_state )
    {
        default:break;
    }
}

void InitState::forceTransition( IState transition_to )
{
    IState prev_state = internal_state;

    internal_state = transition_to;

    if( internal_state != prev_state )
    {
        /* onExit bits */
        switch( prev_state )
        {
            default:break;
        }

        /* onEnter bits */
        switch( internal_state )
        {
            default:break;
        }
    }
}

