#include "DropOffState.h"
#include "../Gripper.h"

void DropOffState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void DropOffState::onEnter( std::string prev_state )
{
    forceTransition( DROPOFF_INIT );
    adjusted = false;
    orientation = TagExaminer::INIT;
    attempts = 0;
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
            break;
        case DROPOFF_FAIL:
            transition_to = "findhome_state";
            break;
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
        case DROPOFF_ADJUST:
            if( adjusted )
            {
                transition_to = DROPOFF_ENTER;
            }
            break;
        case DROPOFF_ENTER:
            if( ( enter && enter->hasArrived() ) || ( inputs->time.toSec() - timer >= DROPOFF_TIME ) )
            {
                delete enter;
                enter = 0;
                outputs->current_waypoint = 0;
                transition_to = DROPOFF_EXIT_BACKUP;
                /* in irl */
                outputs->offset_x = inputs->odom_accel_gps.x;
                outputs->offset_y = inputs->odom_accel_gps.y;
                /* in sim dont change offset */
            }
            break;
        case DROPOFF_EXIT_BACKUP:
            if( exit && exit->hasArrived() )
            {
                delete exit;
                exit = 0;
                outputs->current_waypoint = 0;
                transition_to = DROPOFF_ROTATE;
            }
            break;
        case DROPOFF_ROTATE:
            if( rotate && rotate->hasArrived() )
            {
               delete rotate;
               rotate = 0;
               transition_to = DROPOFF_COMPLETE;
               outputs->current_waypoint = 0;
            }
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
                HomeParams h_params; /* default values should be fine */
                h_params.dist_goal = 0.35;
                this->approach = new ApproachHome( this->inputs, h_params );
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
        {
            if( !alignment || ( alignment && alignment->hasArrived() ) )
            {
                RawOutputParams r_params;
                TagExaminer::Turns desired;

                r_params.duration = 0.15;
                if( this->alignment )
                {
                    delete this->alignment;
                    this->alignment = 0;
                    outputs->current_waypoint = 0;
                }
                desired = inputs->examiner.determineTurning();
                if( orientation == TagExaminer::INIT )
                    orientation = desired;

                if( desired == TagExaminer::STRAIGHT || orientation != desired )
                {
                    adjusted = true;
                }
                else
                {
                    if( desired == TagExaminer::LEFT )
                    {
                        r_params.left_output = -ROTATION_SPEED;
                        r_params.right_output = ROTATION_SPEED;
                    }
                    else
                    {
                        r_params.left_output = ROTATION_SPEED;
                        r_params.right_output = -ROTATION_SPEED;
                    }
                    alignment = new RawOutputWaypoint( inputs, r_params );
                    outputs->current_waypoint = dynamic_cast<Waypoint*>( alignment );
                }
            }
            break;
        }
        case DROPOFF_ENTER:
            break;
        case DROPOFF_EXIT_BACKUP:
            outputs->gripper_position = Gripper::HOVER_OPEN;
            break;
        case DROPOFF_ROTATE:
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
            case DROPOFF_ADJUST:
            {
                if( alignment )
                {
                    delete alignment;
                    alignment = 0;
                }
                break;
            }
            case DROPOFF_ENTER:
            {
                LinearParams l_params;

                l_params.distance = .5;
                l_params.max_output = 45;

                if( this->enter )
                {
                    delete this->enter;
                    this->enter = 0;
                }
                enter = new LinearWaypoint( inputs, l_params );
                outputs->current_waypoint = dynamic_cast<Waypoint*>( enter );
                timer = inputs->time.toSec();
                break;
            }
            case DROPOFF_EXIT_BACKUP:
            {
                LinearParams l_params;

                l_params.distance = 0.6;
                l_params.max_output = 45;
                l_params.reverse = true;

                if( this->exit )
                {
                    delete this->exit;
                    this->exit = 0;
                }

                exit = new LinearWaypoint( inputs, l_params );
                outputs->current_waypoint = dynamic_cast<Waypoint*>( exit );
                break;
            }
            case DROPOFF_ROTATE:
            {
                RotationParams r_params;

                if( this->rotate )
                {
                    delete rotate;
                    rotate = 0;
                }

                r_params.rotate_to = inputs->odom_accel_gps.theta + M_PI;
                r_params.arrived_threshold = M_PI/12;

                rotate = new RotationalWaypoint( inputs, r_params );
                outputs->current_waypoint = dynamic_cast<Waypoint*>( rotate );
                break;
            }
        }
    }
}
