#include "Avoid.h"

void Avoid::action( void )
{
    forceTransition( internalTransition() );
    internalAction();
}

void Avoid::onEnter( std::string prev_state )
{
    attempts = 0;
    previous_state = prev_state;
    forceTransition( AVOID_INIT );

    if( entrance_goal )
    {
        delete entrance_goal;
        entrance_goal = 0;
    }

    SimpleParams params;

    params.skid_steer_threshold = M_PI/6;
    params.arrived_threshold = 0.25;
    params.goal_x = inputs->goal_x;
    params.goal_y = inputs->goal_y;

    entrance_goal = new SimpleWaypoint( inputs, params );
}

void Avoid::onExit( std::string next_state )
{

}

std::string Avoid::transition()
{
    std::string transition_to = getIdentifier();

    if( internal_state == AVOID_EXIT_SUCCESS )
        transition_to = previous_state;
    else if( internal_state == AVOID_EXIT_FAILURE )
    {
        transition_to = previous_state;
        inputs->goalInObst = true;
    }

    return transition_to;
}

ASState Avoid::internalTransition()
{
    ASState transition_to = internal_state;

    switch( internal_state )
    {
        case AVOID_INIT:
            if( rotate )
                transition_to = AVOID_ROTATE;
            break;
        case AVOID_ROTATE:
            std::cout << inputs->us_left << "," << inputs->us_center << "," << inputs->us_right << "," << !TagUtilities::hasTag( &inputs->tags, 256 ) << "," << !TagUtilities::hasTagInRange( &inputs->tags, 0, .21, .4 ) << std::endl;
            if( inputs->us_left > 1.0 && inputs->us_center > 1.0 && inputs->us_right > 1.0 && !TagUtilities::hasTag( &inputs->tags, 256 ) && !TagUtilities::hasTagInRange( &inputs->tags, 0, .21, .4 ) )
            {
                transition_to = AVOID_DRIVE;
            }
            break;
        case AVOID_DRIVE:
            if( inputs->us_left < 0.35 || inputs->us_right < 0.35 || inputs->us_center < .035 || TagUtilities::hasTag( &inputs->tags, 256 ) || TagUtilities::hasTagInRange( &inputs->tags, 0, .21, .4 ) )
            {
                outputs->current_waypoint = 0;
                delete drive;
                drive = 0;

                transition_to = AVOID_ROTATE;
            }
            else if( drive && drive->hasArrived() )
            {
                outputs->current_waypoint = 0;
                delete drive;
                drive = 0;

                transition_to = AVOID_ATTEMPT_EXIT;
                timer = inputs->time.toSec();
            }
            break;
        case AVOID_ATTEMPT_EXIT:
            if( inputs->us_left < 0.35 || inputs->us_right < 0.35 || inputs->us_center < .035 || TagUtilities::hasTag( &inputs->tags, 256 ) || TagUtilities::hasTagInRange( &inputs->tags, 0, .21, .4 ) )
            {
                if( ++attempts > MAX_EXIT_ATTEMPTS )
                    transition_to = AVOID_EXIT_FAILURE;
                else
                    transition_to = AVOID_ROTATE;
            }
            else if( ( inputs->time.toSec() - timer ) > 2.0 )
            {
                transition_to = AVOID_EXIT_SUCCESS;
            }
            break;
        case AVOID_EXIT_FAILURE:
            break;
        case AVOID_EXIT_SUCCESS:
            break;
    }

    return internal_state;
}

void Avoid::internalAction()
{
    switch( internal_state )
    {
        case AVOID_INIT:
        {
            RawOutputParams r_params;

            r_params.left_output = -ROTATION_SPEED;
            r_params.right_output = ROTATION_SPEED;

            rotate = new RawOutputWaypoint( inputs, r_params );
            outputs->current_waypoint = rotate;
            break;
        }
        case AVOID_ROTATE:
            break;
        case AVOID_DRIVE:
            break;
        case AVOID_ATTEMPT_EXIT:
            break;
        case AVOID_EXIT_FAILURE:
            break;
        case AVOID_EXIT_SUCCESS:
            break;
    }
}

void Avoid::forceTransition( ASState transition_to )
{
    ASState prev_state = internal_state;

    internal_state = transition_to;

    if( internal_state != prev_state )
    {
        /* onExit */
        switch( prev_state )
        {
            default:break;
        }

        /* onEnter */
        switch( internal_state )
        {
            default:break;
            case AVOID_ROTATE:
                outputs->current_waypoint = rotate;
                break;
            case AVOID_DRIVE:
            {
                LinearParams l_params;

                l_params.distance = 0.75;
                l_params.max_output = 60;

                drive = new LinearWaypoint( inputs, l_params );
                outputs->current_waypoint = drive;
                break;
            }
        }
    }
}


