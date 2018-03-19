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
    if(prev_state != "avoidcube_state" && prev_state != "avoidhome_state"){
        this->inputs->prevState = prev_state;
        this->inputs->initialAvoidAngle = this->inputs->odom_accel_gps.theta;
        this->inputs->initialAvoidX = this->inputs->odom_accel_gps.x;
        this->inputs->initialAvoidY = this->inputs->odom_accel_gps.y;
    }
    if( waypoints.size() > 0 )
        outputs->current_waypoint = waypoints.front();
}

void AvoidState::onExit( std::string next_state )
{

}

std::string AvoidState::transition()
{
    std::string transition_to = getIdentifier();
    angleToGoal = atan2f(this->inputs->goal_y - this->inputs->odom_accel_gps.y, this->inputs->goal_x - this->inputs->odom_accel_gps.x);
    angleToGoal = this->inputs->odom_accel_gps.theta - angleToGoal;
    double distFromInitialLocation = hypot(this->inputs->odom_accel_gps.x - this->inputs->initialAvoidX, this->inputs->odom_accel_gps.y - this->inputs->initialAvoidY);

    if(angleToGoal < 0 && angleToGoal > -1 && internal_state == AVOID_DRIVE)
        transition_to = this->inputs->prevState;
    if( TagUtilities::hasTag( &this->inputs->tags, 0 ) ){
        if(this->inputs->prevState == "search_state"){
            transition_to = "pickup_state";
        } else if(this->inputs->prevState != "findhome_state"){
            transition_to = "avoidcube_state";
        }
    }
    if( TagUtilities::hasTag(&this->inputs->tags, 256)){
        if(this->inputs->prevState == "findhome_state"){
            transition_to = "dropoff_state";
        } else {
            transition_to = "avoidhome_state";
        }
    }

        
    if( this->inputs->rotationFlag == true && abs(this->inputs->odom_accel_gps.theta) - abs(this->inputs->initialAvoidAngle) < .25 && distFromInitialLocation < .5){
        this->inputs->goalInObst = true;
        transition_to = this->inputs->prevState;
    }


    return transition_to;
}

InternalState AvoidState::internalTransition()
{
    InternalState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case AVOID_INIT:
            if(getNearestUS() > detectionDist + detectionMargin)
                transition_to = AVOID_DRIVE;
            break;
        case AVOID_DRIVE:
            if(getNearestUS() < detectionDist - detectionMargin)
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
            params.left_output = -65;
            params.right_output = 65;
            params.duration = .7;

           break;
        }
        case AVOID_DRIVE:
        {
            if(abs(this->inputs->odom_accel_gps.theta) - abs(this->inputs->initialAvoidAngle) > 1){
                this->inputs->rotationFlag = true;
            }
            params.left_output = 60 * wheelRatio;
            params.right_output = 60 * (1/wheelRatio);
            wheelRatio += 0.05;
            wheelRatio = min(wheelRatio, 4.0);
            break;
        }
    }
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
