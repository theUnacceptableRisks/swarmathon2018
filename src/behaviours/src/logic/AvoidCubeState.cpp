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
    this->waypoints.clear();
    if(prev_state != "avoid_state" && prev_state != "avoidhome_state")
        this->inputs->prevState = prev_state;
    if( waypoints.size() > 0 )
        outputs->current_waypoint = waypoints.front();
    initialTheta = this->inputs->odom_accel_gps.theta;
    initialTime = this->inputs->time.toSec();
    waypointTimer = this->inputs->time.toSec();
    internal_state = AVOIDCUBE_INIT;
}

void AvoidCubeState::onExit( std::string next_state )
{
    this->waypoints.clear();
}

std::string AvoidCubeState::transition()
{
    std::string transition_to = getIdentifier();

    angleToGoal = atan2f(this->inputs->goal_y - this->inputs->odom_accel_gps.y, this->inputs->goal_x - this->inputs->odom_accel_gps.x);
    angleToGoal = this->inputs->odom_accel_gps.theta - angleToGoal;



    if(internal_state == AVOIDCUBE_ESCAPE && this->inputs->time.toSec() - initialTime > 3)
        transition_to = this->inputs->prevState;
    if( TagUtilities::hasTag(&this->inputs->tags, 256)){
        if(this->inputs->prevState == "findhome_state"){
            transition_to = "dropoff_state";
        } else {
            transition_to = "avoidhome_state";
        }
    }

    if( this->inputs->us_center < .4 || this->inputs->us_left < .4 ||  this->inputs->us_right < .4 ){
        transition_to = "avoid_state";
    }

    if(this->inputs->time.toSec() - waypointTimer > 1.5 && internal_state == AVOIDCUBE_DRIVE)
        transition_to = this->inputs->prevState;
    if(transition_to != getIdentifier())
        initialTime = -99;
        
    return transition_to;
}

InternalAvoidCubeState AvoidCubeState::internalTransition()
{
    InternalAvoidCubeState transition_to = internal_state;

    if(initialTime == -99){
        internal_state = AVOIDCUBE_INIT;
        initialTime = this->inputs->time.toSec();
    }



    switch( internal_state )
    {
        default: break;
        case AVOIDCUBE_INIT: 
            if(this->inputs->time.toSec() - waypointTimer > 1.5){
                transition_to = AVOIDCUBE_DRIVE;
                waypointTimer = this->inputs->time.toSec();
            }
            if(this->inputs->time.toSec() - initialTime > 5){
                transition_to = AVOIDCUBE_ESCAPE;
                initialTime = this->inputs->time.toSec();
            }
            break;
        case AVOIDCUBE_DRIVE:
            if(TagUtilities::hasTagInRange(&this->inputs->tags, 0, .21,.4)){
                internal_state = AVOIDCUBE_INIT;
                initialTime = this->inputs->time.toSec();
            }
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
            params.duration = 1.5;
            if(TagUtilities::hasTagInRange(&this->inputs->tags, 0, .21, .4)){
                waypointTimer = this->inputs->time.toSec();
            }
           break;
        }
        case AVOIDCUBE_DRIVE:
        {
            params.left_output = 80;
            params.right_output = 80;
            params.duration = 1.5;
            break;
        }
        case AVOIDCUBE_ESCAPE:
        {
            params.left_output = -80;
            params.right_output = -80;
            params.duration = 3;
            cout << "----ESCAPE------" << endl;
        }
    }  
    waypoint = new RawOutputWaypoint( this->inputs, params );
    this->waypoints.push_back( dynamic_cast<Waypoint*>( waypoint ) );
    this->outputs->current_waypoint = waypoints.front();
    cout << "AVOIDCUBE INTERNAL STATE: " << internal_state << endl;
    if(TagUtilities::hasTag(&this->inputs->tags, 0))
        cout << "NEAREST TAG: " << TagUtilities::getDistance(TagUtilities::getClosestTag(&this->inputs->tags, 0)) << endl;
            
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
