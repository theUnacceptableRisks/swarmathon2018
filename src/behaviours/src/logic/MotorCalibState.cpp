#include "MotorCalibState.h"

void MotorCalibState::action( )
{
    forceTransition( internalTransition() );
    internalAction();
}

void MotorCalibState::onEnter( std::string prev_state )
{
    forceTransition( MOTORCALIB_INIT );
}

void MotorCalibState::onExit( std::string next_state )
{

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
            break;
        case MOTORCALIB_DRIVE:
            break;
        case MOTORCALIB_CHECK:
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
            break;
        case MOTORCALIB_DRIVE:
            break;
        case MOTORCALIB_CHECK:
            break;
        case MOTORCALIB_COMPLETE:
            break;
    }

}

void forceTransition( MCState transition_to )
{

}


