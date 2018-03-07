#include "DropOffState.h"
#include "../Gripper.h"

void DropOffState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void DropOffState::onEnter( std::string prev_state )
{
    if( prev_state == "findhome_state" )
    {
        forceTransition( DROPOFF_INIT );
    }
}

void DropOffState::onExit( std::string nexst_state )
{

}

std::string DropOffState::transition()
{
    std::string transition_to = getIdentifier();

    switch( internal_state )
    {
        default:break;
        case DROPOFF_COMPLETE:
            transition_to = "search_state";
        case DROPOFF_FAIL:
            transition_to = "findhome_state";
    }

    return transition_to;
}

DOState DropOffState::internalTransition()
{
    DOState transition_to = internal_state;

    switch( internal_state )
    {
        default:break;
        case DROPOFF_INIT:
            if( this->approach )
                transition_to = DROPOFF_APPROACH;
            else if( attempts > DROPOFF_MAX_ATTEMPTS )
                transition_to = DROPOFF_FAIL;
            break;
        case DROPOFF_APPROACH:
            if( this->approach && this->approach->hasArrived() )
            {
                delete this->approach;
                this->approach = 0;
                this->outputs->current_waypoint = 0;

                transition_to = DROPOFF_ADJUST;
            }
            else if( attempts > DROPOFF_MAX_ATTEMPTS )
                transition_to = DROPOFF_FAIL;
            break;
    }

    return transition_to;
}

void DropOffState::internalAction()
{
    switch( internal_state )
    {
        default:break;
        case DROPOFF_INIT:
        {
            if( TagUtilities::hasTag( &inputs->tags, 256 ) )
            {
                TagParams t_params;

                t_params.desired_tag = 256;

                t_params.dist_deccel = 0.05;
                t_params.dist_goal = 0.40;
                t_params.dist_max_output = 10;

                t_params.yaw_deccel = 0.10;
                t_params.yaw_goal = 0.0;
                t_params.yaw_max_output = 1;

                t_params.type = CLOSEST;
                t_params.skid_rotate_threshold = 0.02;

                this->approach = new ApproachTagWaypoint( this->inputs, t_params );
                this->outputs->current_waypoint = this->approach;
                this->attempts = 0;
            }
            else
            {
                this->attempts++;
            }
            break;
        }

        case DROPOFF_APPROACH:
            if( TagUtilities::hasTag( &this->inputs->tags, 256 ) )
            {
                this->attempts = 0;
            }
            else
            {
                this->attempts++;
            }
            break;
        case DROPOFF_ADJUST:
            std::cout << "Made it to adjust" << std::endl;
            break;
    }
}

void DropOffState::forceTransition( DOState transition_to )
{
    DOState prev_state = internal_state;

    internal_state = transition_to;

    if( internal_state != prev_state )
    {
        /* on Exit */
        switch( prev_state )
        {
            default:break;
        }

        /* on Enter */
        switch( internal_state )
        {
            default: break;
            case DROPOFF_INIT:
                if( this->approach )
                {
                    delete this->approach;
                    this->approach = 0;
                }
                break;
        }
    }
}
