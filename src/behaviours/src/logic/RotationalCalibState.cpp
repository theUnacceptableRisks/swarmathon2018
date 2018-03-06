#include "RotationalCalibState.h"

void RotationalCalibState::action( )
{
    forceTransition( internalTransition() );
    internalAction();
}

void RotationalCalibState::onEnter( std::string prev_state )
{
    this->current_PWM = 0;
    forceTransition( ROTATIONALCALIB_INIT );
}

void RotationalCalibState::onExit( std::string next_state )
{
    this->inputs->calibration.rotational_min = this->current_PWM;
    this->inputs->controller.changeRotationalMin( this->current_PWM );
    std::cout << "Rotational Calibration: " << this->current_PWM << std::endl;
}

std::string RotationalCalibState::transition()
{
    std::string transition_to = getIdentifier();

    if( internal_state == ROTATIONALCALIB_COMPLETE )
        transition_to = "search_state";

    return transition_to;
}

MCState RotationalCalibState::internalTransition()
{
    MCState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case ROTATIONALCALIB_INIT:
        {
            if( current_PWM != 0 )
                transition_to = ROTATIONALCALIB_DRIVE;
            break;
        }
        case ROTATIONALCALIB_DRIVE:
        {
            if( waypoint && waypoint->hasArrived() )
                transition_to = ROTATIONALCALIB_CHECK;
            break;
        }
        case ROTATIONALCALIB_CHECK:
            if( found_optimal )
                transition_to = ROTATIONALCALIB_COMPLETE;
            else
                transition_to = ROTATIONALCALIB_DRIVE;
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
        case ROTATIONALCALIB_DRIVE:
            break;
        case ROTATIONALCALIB_CHECK:
        {
            if( fabs( this->inputs->raw_odom.x - this->prev_x ) > MIN_DISTANCE )
                found_optimal = true;
            else
                found_optimal = false;
            break;
        }
        case ROTATIONALCALIB_COMPLETE:
            break;
    }

}

void RotationalCalibState::forceTransition( MCState transition_to )
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
            case ROTATIONALCALIB_DRIVE:
            {
                RawOutputParams params;

                this->current_PWM++;
                params.left_output = (-1)*this->current_PWM;
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


