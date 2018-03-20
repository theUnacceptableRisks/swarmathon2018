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
    return transition_to;
}

IState InitState::internalTransition()
{
    IState transition_to = internal_state;
    switch( internal_state )
    {
        default:break;
        case INIT_START:
            if( drive )
            {
                transition_to = INIT_APPROACH;
            }
            break;
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
               transition_to = INIT_BACKUP;
            }
            break;
        case INIT_BACKUP:
            if( drive && drive->hasArrived() )
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
        case INIT_START:
        {
            RawOutputParams params;

            params.left_output = PWM_OUTPUT;
            params.right_output = PWM_OUTPUT;
            params.duration = GIVE_UP_TIME;

            drive = new RawOutputWaypoint( inputs, params );
            outputs->current_waypoint = dynamic_cast<Waypoint*>( drive );
            start_time = inputs->time.toSec();
            break;
        }
        case INIT_APPROACH:
            break;
        case INIT_CALIBRATE:
        {
            if( inputs->tags.size() > 0 )
            {
                Tag closest_tag = TagUtilities::getClosestTag( &inputs->tags, 256 );
                double z = closest_tag.getPositionZ();
                double dist = 0;
                if( z == 0 )
                    dist = DISTANCE_TO_CENTER + 0.1;
                else
                    dist = sqrt( ( z * z ) - ( 0.195 * 0.195 ) ) + DISTANCE_TO_CENTER;

                /* in sim */
                outputs->offset_x = dist * cos( inputs->odom_accel.theta ) + inputs->odom_accel.x;
                outputs->offset_y = dist * sin( inputs->odom_accel.theta ) + inputs->odom_accel.y;
                /* irl */
//                outputs->offset_x = dist * cos( inputs->odom_accel_gps.theta ) + inputs->odom_accel_gps.x;
//                outputs->offset_y = dist * sin( inputs->odom_accel_gps.theta ) + inputs->odom_accel_gps.y;
                calibration_complete = true;
            }
            break;
        }
        case INIT_BACKUP:
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
            case INIT_APPROACH:
                if( drive )
                {
                    delete drive;
                    drive = 0;
                    outputs->current_waypoint = 0;
                }
                break;
        }

        /* onEnter bits */
        switch( internal_state )
        {
            default:break;
            case INIT_BACKUP:
            {
                if( drive )
                {
                    delete drive;
                    drive = 0;
                }

                RawOutputParams params;

                params.left_output = -PWM_OUTPUT;
                params.right_output = -PWM_OUTPUT;
                params.duration = inputs->time.toSec() - start_time;;

                drive = new RawOutputWaypoint( inputs, params );
                outputs->current_waypoint = dynamic_cast<Waypoint*>( drive );
                break;
            }
        }
    }
}

