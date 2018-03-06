#include "MotorCalibState.h"

void MotorCalibState::action( )
{
    forceTransition( internalTransition() );
    internalAction();
}

void MotorCalibState::onEnter( std::string prev_state )
{
    this->current_PWM = 0;
    forceTransition( MOTORCALIB_INIT );
}

void MotorCalibState::onExit( std::string next_state )
{
    this->inputs->calibration.motor_min = this->current_PWM;
    this->inputs->controller.changeMotorMin( this->current_PWM );
    std::cout << "Current Calibration: " << this->current_PWM << std::endl;
}

std::string MotorCalibState::transition()
{
    std::string transition_to = getIdentifier();

    if( internal_state == MOTORCALIB_COMPLETE )
        transition_to = "search_state";

    return transition_to;
}

MCState MotorCalibState::internalTransition()
{
    MCState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case MOTORCALIB_INIT:
        {
            if( current_PWM != 0 )
                transition_to = MOTORCALIB_DRIVE;
            break;
        }
        case MOTORCALIB_DRIVE:
        {
            if( waypoint && waypoint->hasArrived() )
                transition_to = MOTORCALIB_CHECK;
            break;
        }
        case MOTORCALIB_CHECK:
            if( found_optimal )
                transition_to = MOTORCALIB_COMPLETE;
            else
                transition_to = MOTORCALIB_DRIVE;
            break;
        case MOTORCALIB_COMPLETE:
            break;
    }

    return transition_to;
}

void MotorCalibState::internalAction()
{
    switch( internal_state )
    {
        default: break;
        case MOTORCALIB_INIT:
            this->current_PWM = this->inputs->calibration.motor_min;
            break;
        case MOTORCALIB_DRIVE:
            break;
        case MOTORCALIB_CHECK:
        {
            if( fabs( this->inputs->raw_odom.x - this->prev_x ) > MIN_DISTANCE )
                found_optimal = true;
            else
                found_optimal = false;
            break;
        }
        case MOTORCALIB_COMPLETE:
            break;
    }

}

void MotorCalibState::forceTransition( MCState transition_to )
{
    MCState prev_state = internal_state;

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
            case MOTORCALIB_DRIVE:
            {
                RawOutputParams params;

                this->current_PWM++;
                params.left_output = this->current_PWM;
                params.right_output = this->current_PWM;
                params.duration = CALIB_DRIVE_DURATION;

                if( this->waypoint )
                {
                    delete this->waypoint;
                    this->waypoint = 0;
                }
                this->waypoint = new RawOutputWaypoint( this->inputs, params );
                this->outputs->current_waypoint = dynamic_cast<Waypoint*>( this->waypoint );

                prev_x = this->inputs->raw_odom.x;
                break;
            }
        }
    }
}


