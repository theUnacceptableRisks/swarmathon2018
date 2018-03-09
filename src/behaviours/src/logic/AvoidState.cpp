#include <iostream>
#include "AvoidState.h"
#include "../TagUtilities.h"
#include "../waypoints/RawOutputWaypoint.h"

void AvoidState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void AvoidState::onEnter( std::string prev_state )
{
    previousState = prev_state;
    if( waypoints.size() > 0 )
        outputs->current_waypoint = waypoints.front();
    initialTheta = this->inputs->odom_accel_gps.theta;
}

void AvoidState::onExit( std::string next_state )
{

}

std::string AvoidState::transition()
{
    std::string transition_to = getIdentifier();

    //if( (internal_state == AVOID_DRIVE && wheelRatio < 3 && getNearestUS() > 1.5 && (this->inputs->odom_accel_gps.theta > initialTheta || this->inputs->odom_accel_gps.theta < initialTheta - 3.1415926 ))|| wheelRatio > 4)
    if(wheelRatio == 4)
        transition_to = previousState;
    return transition_to;
}

InternalState AvoidState::internalTransition()
{
    InternalState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case AVOID_INIT:
            if(getNearestUS() > 2)
                transition_to = AVOID_DRIVE;
            break;
        case AVOID_DRIVE:
            if(getNearestUS() < .4)
                transition_to = AVOID_INIT;
            break;
    }

    return transition_to;
}

void AvoidState::internalAction()
{
    RawOutputWaypoint *waypoint = 0;
    RawOutputParams params;
    this->waypoints.clear();
    switch( internal_state )
    {
        default: break;
        case AVOID_INIT:
        {
            wheelRatio = 1;
            params.left_output = -40;
            params.right_output = 40;
            params.duration = .7;
            std::cout << "AVOID INIT" << endl;
            std::cout << "NEAREST US: " << getNearestUS() << endl;
           break;
        }
        case AVOID_DRIVE:
        {
            params.left_output = 60 * wheelRatio;
            params.right_output = 60 * (1/wheelRatio);
            wheelRatio += 0.05;
            wheelRatio = min(wheelRatio, 4.0);
            std::cout << "AVOID DRIVE" << endl;
            std::cout << "NEAREST US: " << getNearestUS() << endl;
            break;
        }
    }
    std::cout << "INITIAL THETA: " << initialTheta << endl;
    std::cout << "CURRENT THETA: " << this->inputs->odom_accel_gps.theta  << endl;
    std::cout << "WheelRatio: " << wheelRatio << endl;
    waypoint = new RawOutputWaypoint( this->inputs, params );
    this->waypoints.push_back( dynamic_cast<Waypoint*>( waypoint ) );
    this->outputs->current_waypoint = waypoints.front();
            
}

void AvoidState::forceTransition( InternalState transition_to )
{
    InternalState prev_state = internal_state;

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
        }

    }
}

double AvoidState::getNearestUS (){
    cout << "L: " << this->inputs->us_left <<  "C: " << this->inputs->us_center <<  "R: " << this->inputs->us_right << endl;
    return min(min(this->inputs->us_left, this->inputs->us_right),this->inputs->us_center);
}
