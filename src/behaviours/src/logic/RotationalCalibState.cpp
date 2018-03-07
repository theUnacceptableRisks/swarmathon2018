#include "RotationalCalibState.h"

void RotationalCalibState::action( )
{
    forceTransition( internalTransition() );
    internalAction();
    std::cout << "Current Rotational State: " << this->internal_state << std::endl;
}

void RotationalCalibState::onEnter( std::string prev_state )
{
    this->prev_x = this->inputs->raw_odom.x;
    this->current_PWM = 0;
    forceTransition( ROTATIONALCALIB_INIT );
}

void RotationalCalibState::onExit( std::string next_state )
{
    this->inputs->calibration.rotational_min = this->current_PWM;
    this->inputs->controller.changeRotationalMin( this->current_PWM );
}

std::string RotationalCalibState::transition()
{
    std::string transition_to = getIdentifier();

    if( internal_state == ROTATIONALCALIB_COMPLETE )
        transition_to = "search_state";

    return transition_to;
}

RCState RotationalCalibState::internalTransition()
{
    RCState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case ROTATIONALCALIB_INIT:
        {
            if( current_PWM != 0 )
                transition_to = ROTATIONALCALIB_APPROACH_HOME;
            break;
        }
        case ROTATIONALCALIB_APPROACH_HOME:
            if( TagUtilities::hasTag( &this->inputs->tags, 256 ) && this->inputs->tags.size() > 4 && TagUtilities::getDistance( this->inputs->tags.back() ) < .26 )
                transition_to = ROTATIONALCALIB_ATTEMPT_ROTATION;
            break;
        case ROTATIONALCALIB_ATTEMPT_ROTATION:
            if( this->waypoint && this->waypoint->hasArrived() )
            {
                this->outputs->current_waypoint = 0;
                delete this->waypoint;
                this->waypoint = 0;

                transition_to = ROTATIONALCALIB_CHECK;
            }
            break;
        case ROTATIONALCALIB_CHECK:
            if( found_optimal )
                transition_to = ROTATIONALCALIB_COMPLETE;
            else
                transition_to = ROTATIONALCALIB_ATTEMPT_ROTATION;
            break;
        case ROTATIONALCALIB_COMPLETE:
            break;
    }

    return transition_to;
}

void RotationalCalibState::internalAction()
{
    switch( internal_state )
    {
        default: break;
        case ROTATIONALCALIB_INIT:
            this->current_PWM = this->inputs->calibration.rotational_min;
            break;
        case ROTATIONALCALIB_APPROACH_HOME:
            break;
        case ROTATIONALCALIB_ATTEMPT_ROTATION:
            break;
        case ROTATIONALCALIB_CHECK:
        {
            if( fabs( this->inputs->tags.back().getPositionX() - this->prev_x ) > MIN_ROT_DISTANCE )
                found_optimal = true;
            else
                found_optimal = false;
            break;
        }
        case ROTATIONALCALIB_COMPLETE:
            break;
    }

}

void RotationalCalibState::forceTransition( RCState transition_to )
{
    RCState prev_state = internal_state;

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
            case ROTATIONALCALIB_APPROACH_HOME:
            {
                RawOutputParams params;

                params.left_output = this->inputs->calibration.motor_min + 5;
                params.right_output = this->inputs->calibration.motor_min + 5;

                if( this->waypoint )
                {
                    delete this->waypoint;
                    this->waypoint = 0;
                }

                this->waypoint = new RawOutputWaypoint( this->inputs, params );
                this->outputs->current_waypoint = dynamic_cast<Waypoint*>( this->waypoint );
                break;
            }
            case ROTATIONALCALIB_ATTEMPT_ROTATION:
            {
                RawOutputParams params;

                this->current_PWM++;
                if( rot_direction == 0 )
                {
                    params.left_output = (-1)*this->current_PWM;
                    params.right_output = this->current_PWM;
                    rot_direction = 1;
                }
                else
                {
                    params.left_output = this->current_PWM;
                    params.right_output = (-1)*this->current_PWM;
                    rot_direction = 0;
                }
                params.duration = CALIB_ROT_DURATION;

                if( this->waypoint )
                {
                    delete this->waypoint;
                    this->waypoint = 0;
                }
                this->waypoint = new RawOutputWaypoint( this->inputs, params );
                this->outputs->current_waypoint = dynamic_cast<Waypoint*>( this->waypoint );

                prev_x = this->inputs->tags.back().getPositionX();
                break;
            }
        }
    }
}


