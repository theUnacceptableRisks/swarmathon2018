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
                delete this->approach;
                this->approach = 0;

                transition_to = PICKUP_FINAL_APPROACH;
                /* on Enter */
                LinearParams l_params;

                l_params.distance = 0.11;
                l_params.deccel_point = 0;
                l_params.max_vel = 5;

                this->linear = new LinearWaypoint( inputs, l_params );
                outputs->current_waypoint = linear;
            }
            break;
        case PICKUP_FINAL_APPROACH:
            if( linear && linear->hasArrived() )
            {
                outputs->current_waypoint = 0;
                delete this->linear;
                this->linear = 0;

                transition_to = PICKUP_CLAW_CLOSE;
                this->timer = this->inputs->time.toSec();
            }
            break;
        case PICKUP_CLAW_CLOSE:
            if( ( this->inputs->time.toSec() - this->timer ) >= 0.75 )
            {
                transition_to = PICKUP_CLAW_UP;
                this->timer = this->inputs->time.toSec();
            }
            break;
        case PICKUP_CLAW_UP:
            if( ( this->inputs->time.toSec() - this->timer ) >= 0.75 )
            {
                transition_to = PICKUP_CONFIRM;
            }
            break;
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
                approach = new ApproachTagWaypoint( inputs, 0, 0.2 );
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
        case PICKUP_FINAL_APPROACH:
            outputs->gripper_position = Gripper::DOWN_OPEN;
            break;
        case PICKUP_CLAW_CLOSE:
            outputs->gripper_position = Gripper::DOWN_CLOSED;
            break;
        case PICKUP_CLAW_UP:
            outputs->gripper_position = Gripper::UP_CLOSED;
            break;
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
