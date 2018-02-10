#include "PickUpState.h"
#include "../Gripper.h"

/********************
 * Basic Operations *
 ********************/

void PickUpState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void PickUpState::onEnter()
{
    forceTransition( PICKUP_INIT );
}

void PickUpState::onExit()
{

}

std::string PickUpState::transition()
{
    std::string transition_to = getIdentifier();
    return transition_to;
}

/***********************
 * Internal Operations *
 ***********************/
PUState PickUpState::internalTransition()
{
    PUState transition_to = internal_state;

    switch( internal_state )
    {
        case PICKUP_INIT:
            if( approach )
            {
                transition_to = PICKUP_APPROACH;
            }
            else
            {
                if( attempts > MAX_ATTEMPTS )
                    transition_to = PICKUP_FAIL;

            }
            break;
        case PICKUP_APPROACH:
            if( approach && approach->hasArrived() )
            {
                outputs->current_waypoint = 0;
                delete approach;
                approach = 0;

                transition_to = PICKUP_CLAW_DOWN;
            }
            break;
        case PICKUP_CLAW_DOWN:
        case PICKUP_CLAW_CLOSE:
        case PICKUP_CLAW_UP:
        case PICKUP_CONFIRM:
        case PICKUP_HOVER_CLOSE:
        case PICKUP_COMPLETE:
        case PICKUP_FAIL:
            break;
    }
    return transition_to;
}

void PickUpState::internalAction()
{
    switch( internal_state )
    {
        case PICKUP_INIT:
            if( TagUtilities::hasTag( &inputs->tags, 0 ) )
            {
                approach = new ApproachTagWaypoint( inputs, 0, TagUtilities::getDistance( inputs->tags.back() ) );
                outputs->current_waypoint = approach;
            }
            else
            {
                attempts++;
            }
            break;
        case PICKUP_APPROACH:
            std::cout << "approaching" << std::endl;
            outputs->gripper_position = Gripper::DOWN_OPEN;
            //does nothing for now
            break;
        case PICKUP_CLAW_DOWN:
            outputs->gripper_position = Gripper::DOWN_CLOSED;
            break;
        case PICKUP_CLAW_CLOSE:
        case PICKUP_CLAW_UP:
        case PICKUP_CONFIRM:
        case PICKUP_HOVER_CLOSE:
        case PICKUP_COMPLETE:
        case PICKUP_FAIL:
            break;

    }
}

void PickUpState::forceTransition( PUState transition_to )
{
    internal_state = transition_to;
}
