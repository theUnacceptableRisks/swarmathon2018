#include <iostream>
#include "AvoidCubeState.h"
#include "../TagUtilities.h"
#include "../waypoints/RawOutputWaypoint.h"

void AvoidCubeState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void AvoidCubeState::onEnter( std::string prev_state )
{
    previousState = prev_state;
    if( waypoints.size() > 0 )
        outputs->current_waypoint = waypoints.front();
    initialTheta = this->inputs->odom_accel_gps.theta;
}

void AvoidCubeState::onExit( std::string next_state )
{

}

std::string AvoidCubeState::transition()
{
    std::string transition_to = getIdentifier();

    angleToGoal = atan2f(this->inputs->goal_y - this->inputs->odom_accel_gps.y, this->inputs->goal_x - this->inputs->odom_accel_gps.x);
    angleToGoal = this->inputs->odom_accel_gps.theta - angleToGoal;

    if(angleToGoal < 0 && angleToGoal > -1 && internal_state == AVOIDCUBE_DRIVE)
        transition_to = previousState;
    if(wheelRatio >= 4)
        transition_to = previousState;

    return transition_to;
}

InternalAvoidCubeState AvoidCubeState::internalTransition()
{
    InternalAvoidCubeState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case AVOIDCUBE_INIT:
            if(!TagUtilities::hasTag(&this->inputs->tags , 0 ))
                transition_to = AVOIDCUBE_DRIVE;
            break;
        case AVOIDCUBE_DRIVE:
            if(TagUtilities::hasTag(&this->inputs->tags , 0 ))
                transition_to = AVOIDCUBE_INIT;
            break;
    }

    return transition_to;
}

void AvoidCubeState::internalAction()
{
    RawOutputWaypoint *waypoint = 0;
    RawOutputParams params;
    this->waypoints.clear();
    switch( internal_state )
    {
        default: break;
        case AVOIDCUBE_INIT:
        {
            wheelRatio = 1;
            params.left_output = -80;
            params.right_output = 80;
            params.duration = .7;
            std::cout << "AVOID INIT" << endl;
            std::cout << "NEAREST US: " << getNearestUS() << endl;
           break;
        }
        case AVOIDCUBE_DRIVE:
        {
            params.left_output = 60 * wheelRatio;
            params.right_output = 60 * (1/wheelRatio);
            wheelRatio += 0.04;
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

void AvoidCubeState::forceTransition( InternalAvoidCubeState transition_to )
{
    InternalAvoidCubeState prev_state = internal_state;

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

double AvoidCubeState::getNearestUS (){
    cout << "L: " << this->inputs->us_left <<  "C: " << this->inputs->us_center <<  "R: " << this->inputs->us_right << endl;
    return min(min(this->inputs->us_left, this->inputs->us_right),this->inputs->us_center);
}
