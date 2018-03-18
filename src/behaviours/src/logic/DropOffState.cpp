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
            if( yaw_average > YAW_LOW_RANGE && yaw_average < YAW_HIGH_RANGE )
            {
                delete alignment;
                alignment = 0;
                outputs->current_waypoint = 0;

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
            }
            break;
        case DROPOFF_EXIT_BACKUP:
            if( exit && exit->hasArrived() )
            {
                delete exit;
                exit = 0;
                outputs->current_waypoint = 0;
                transition_to = DROPOFF_COMPLETE;
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
            int count = 0;
            yaw_average = 0;
            if( TagUtilities::hasTag( &inputs->tags, 256 ) )
            {
                for( int i = 0; i < inputs->tags.size(); i++ )
                {
                    Tag curr_tag = inputs->tags.at(i);
                    if( curr_tag.getID() == 256 )
                    {
                        yaw_average += curr_tag.calcYaw();
                        count++;
                    }
                }
                yaw_average /= (double)count;
            }
            break;
        }
        case DROPOFF_ENTER:
            break;
        case DROPOFF_EXIT_BACKUP:
            outputs->gripper_position = Gripper::HOVER_OPEN;
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
                RawOutputParams r_params;

                if( this->alignment )
                {
                    delete this->alignment;
                    this->alignment = 0;
                }
                if( inputs->examiner.determineTurning() == TagExaminer::LEFT )
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
                break;
            }
            case DROPOFF_ENTER:
            {
                LinearParams l_params;

                l_params.distance = .5;
                l_params.max_output = 30;

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
                l_params.max_output = 25;
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
        }
    }
}
