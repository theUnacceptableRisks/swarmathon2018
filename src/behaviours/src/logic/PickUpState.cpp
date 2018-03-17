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

void PickUpState::onEnter( std::string prev_state )
{
    forceTransition( PICKUP_INIT );
    num_tries = 0;
    attempts = 0;
    cube_secured = false;
}

void PickUpState::onExit( std::string next_state )
{
    if( this->approach )
    {
        delete this->approach;
        this->approach = 0;
    }

    if( this->linear )
    {
        delete this->linear;
        this->linear = 0;
    }
}

std::string PickUpState::transition()
{
    std::string transition_to = getIdentifier();

    switch( internal_state )
    {
        case PICKUP_COMPLETE:
            if( ( this->inputs->time.toSec() - this->timer ) >= 1.5 )
                transition_to = "findhome_state";
            break;
        case PICKUP_COMPLETE_FAILURE:
            transition_to = "search_state";
            break;
    }

    return transition_to;
}

/***********************
 * Internal Operations *
 ***********************/
PUState PickUpState::internalTransition()
{
    PUState transition_to = internal_state;
    std::cout << "Current State: " << transition_to << std::endl;
    switch( internal_state )
    {
        case PICKUP_INIT:
            if( approach )
            {
                transition_to = PICKUP_APPROACH;
            }
            else
            {
                if( this->attempts > MAX_ATTEMPTS )
                    transition_to = PICKUP_COMPLETE_FAILURE;
            }
            break;
        case PICKUP_COMPLETE_FAILURE:
            //complete do nothing state
            break;
        case PICKUP_APPROACH:
            if( approach && approach->hasArrived() )
            {
                outputs->current_waypoint = 0;
                delete this->approach;
                this->approach = 0;

                transition_to = PICKUP_FINAL_APPROACH;
            }
            else if( attempts > MAX_ATTEMPTS )
            {
                transition_to = PICKUP_COMPLETE_FAILURE;
            }
            break;
        case PICKUP_FINAL_APPROACH:
            if( this->linear && this->linear->hasArrived() )
            {
                outputs->current_waypoint = 0;
                delete this->linear;
                this->linear = 0;

                this->timer = this->inputs->time.toSec();
                transition_to = PICKUP_CLAW_CLOSE;
            }
            break;
        case PICKUP_CLAW_CLOSE:
            if( ( this->inputs->time.toSec() - this->timer ) >= CLOSE_TIME )
            {
                transition_to = PICKUP_CLAW_UP;
                this->timer = this->inputs->time.toSec();
            }
            break;
        case PICKUP_CLAW_UP:
            if( ( this->inputs->time.toSec() - this->timer ) >= UP_TIME )
            {
                transition_to = PICKUP_CONFIRM;
                this->timer = this->inputs->time.toSec();
            }
            break;
        case PICKUP_CONFIRM:
            if( cube_secured )
            {
                transition_to = PICKUP_COMPLETE;
                this->timer = this->inputs->time.toSec();
            }
            else if( ( this->inputs->time.toSec() - this->timer ) >= CONFIRM_TIME )
            {
                transition_to = PICKUP_FAIL;
            }
            break;
        case PICKUP_COMPLETE:
            break;
        case PICKUP_FAIL:
            if( linear && linear->hasArrived() )
            {
                transition_to = PICKUP_INIT;
            }
            break;
    }
    return transition_to;
}

void PickUpState::internalAction()
{
    switch( internal_state )
    {
        case PICKUP_INIT:
            if( inputs->cubes.size() > 0 )
            {
                CubeParams c_params;

                c_params.dist_goal = 0.24;
                c_params.dist_max_output = 10;

                c_params.yaw_goal = CAMERA_OFFSET;
                c_params.yaw_max_output = 80;

                c_params.skid_rotate_threshold = 0.05;

                approach = new ApproachCube( inputs, c_params );
                outputs->current_waypoint = approach;
            }
            else
            {
                this->attempts++;
            }
            break;
        case PICKUP_COMPLETE_FAILURE:
            //complete do nothing state
            break;
        case PICKUP_APPROACH:
            outputs->gripper_position = Gripper::DOWN_OPEN;
            if( TagUtilities::hasTag( &inputs->tags, 0 ) )
                this->attempts = 0;
            else
                this->attempts++;
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
            if( TagUtilities::hasTag( &this->inputs->tags, 0 ) && TagUtilities::getDistance( TagUtilities::getClosestTag( &this->inputs->tags, 0 ) ) < 0.15 )
                cube_secured = true;
            break;
        case PICKUP_COMPLETE:
            outputs->gripper_position = Gripper::HOVER_CLOSED;
            break;
        case PICKUP_FAIL:
            std::cout << "In Pickup Fail" << std::endl;
            outputs->gripper_position = Gripper::DOWN_OPEN;
            break;

    }
}

void PickUpState::forceTransition( PUState transition_to )
{
    PUState prev_state = internal_state;

    /* transition */
    internal_state = transition_to;

    if( internal_state != prev_state )
    {

        /* onExit bits */
        switch( prev_state )
        {
            default: break;
        }

        /* onEnter bits */
        switch( internal_state )
        {
            default: break;
            case PICKUP_FINAL_APPROACH:
            {
                if( this->linear )
                {
                    delete this->linear;
                    this->linear = 0;
                }
                /* on Enter */
                LinearParams l_params;

                l_params.distance = TagUtilities::getClosestCube( &inputs->cubes ).getGroundDistance();
                l_params.max_output = 25;

                this->linear = new LinearWaypoint( this->inputs, l_params );
                this->outputs->current_waypoint = this->linear;
                break;
            }
            case PICKUP_FAIL:
            {
                /* on Enter */
                if( this->linear )
                {
                    delete this->linear;
                    this->linear = 0;
                }
                this->num_tries++;

                LinearParams l_params;

                l_params.distance = 0.3;
                l_params.max_output = 20;
                l_params.reverse = true;

                this->linear = new LinearWaypoint( this->inputs, l_params );
                this->outputs->current_waypoint = this->linear;
                break;
            }
        }
    }
}
