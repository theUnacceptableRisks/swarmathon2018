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
        case INIT_APPROACH:
            if( drive && drive->hasArrived() )
            {
                transition_to = INIT_FAIL;
            }
            else if( TagUtilities::numberOfTags( &inputs->tags, 256 ) > 3 )
            {
                transition_to = INIT_CALIBRATE;
            }
            break;
        case INIT_CALIBRATE:
            if( calibration_complete )
            {
               transition_to = INIT_COMPLETE;
            }
            break;
        case INIT_COMPLETE:
            break;
        case INIT_FAIL:
            break;
    }

    return transition_to;
}

void InitState::internalAction()
{
    switch( internal_state )
    {
        default:break;
        case INIT_APPROACH:
            break;
        case INIT_CALIBRATE:
            /* in sim */
            outputs->offset_x = DISTANCE_TO_CENTER * cos( inputs->odom_accel.theta ) + inputs->odom_accel.x;
            outputs->offset_y = DISTANCE_TO_CENTER * sin( inputs->odom_accel.theta ) + inputs->odom_accel.y;
            /* irl */
            //outputs->offset_x = DISTANCE_TO_CENTER * cos( inputs->odom_accel_gps.theta ) + inputs->odom_accel_gps.x;
            //outputs->offset_y = DISTANCE_TO_CENTER * sin( inputs->odom_accel_gps.theta ) + inputs->odom_accel_gps.y;
            calibration_complete = true;
            break;
        case INIT_COMPLETE:
            break;
        case INIT_FAIL:
            break;
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

