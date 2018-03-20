#include <iostream>
#include "AvoidHomeState.h"
#include "../TagUtilities.h"
#include "../waypoints/RawOutputWaypoint.h"

void AvoidHomeState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void AvoidHomeState::onEnter( std::string prev_state )
{
    if(prev_state != "avoidcube_state" && prev_state != "avoid_state"){
        this->inputs->prevState = prev_state;
        this->inputs->initialAvoidAngle = this->inputs->odom_accel_gps.theta;
        this->inputs->initialAvoidX = this->inputs->odom_accel_gps.x;
        this->inputs->initialAvoidY = this->inputs->odom_accel_gps.y;
        initialTime = this->inputs->time.toSec();
    }
    if( waypoints.size() > 0 )
        outputs->current_waypoint = waypoints.front();
    /* in irl */
//    outputs->offset_x = inputs->odom_accel_gps.x;
  //  outputs->offset_y = inputs->odom_accel_gps.y;
    /* in sim dont change offset */
}

void AvoidHomeState::onExit( std::string next_state )
{
    initialTime = -99;
}

std::string AvoidHomeState::transition()
{
   
    std::string transition_to = getIdentifier();

    angleToGoal = atan2f(this->inputs->goal_y - this->inputs->odom_accel_gps.y, this->inputs->goal_x - this->inputs->odom_accel_gps.x);
    angleToGoal = this->inputs->odom_accel_gps.theta - angleToGoal;
    double distFromInitialLocation = hypot(this->inputs->odom_accel_gps.x - this->inputs->initialAvoidX, this->inputs->odom_accel_gps.y - this->inputs->initialAvoidY);


    if(internal_state == AVOIDHOME_ESCAPE && this->inputs->time.toSec() - initialTime > 3.0)
        transition_to = this->inputs->prevState;


    if( TagUtilities::hasTag( &this->inputs->tags, 0 ) ){
        if(this->inputs->prevState == "search_state"){
            transition_to = "pickup_state";
        } else {
            transition_to = "avoidcube_state";
        }
    } else if(this->inputs->us_center < .4 || this->inputs->us_left < .4 ||  this->inputs->us_right < .4 ){
        transition_to = "avoid_state";
    } else if(angleToGoal < 0 && angleToGoal > -1 && internal_state == AVOIDHOME_DRIVE){
        transition_to = this->inputs->prevState;
    }
        
    if( this->inputs->rotationFlag == true && abs(this->inputs->odom_accel_gps.theta) - abs(this->inputs->initialAvoidAngle) < .25 && distFromInitialLocation < .5){
        this->inputs->goalInObst = true;
        this->inputs->rotationFlag = false;
        transition_to = this->inputs->prevState;
    }

    return transition_to;
}

InternalAvoidHomeState AvoidHomeState::internalTransition()
{
    InternalAvoidHomeState transition_to = internal_state;

    if(initialTime == -99){
        internal_state = AVOIDHOME_INIT;
        initialTime = this->inputs->time.toSec();
    }
    switch( internal_state )
    {
        default: break;
        case AVOIDHOME_INIT:
        {
            if(!TagUtilities::hasTag(&this->inputs->tags , 256 ) && this->inputs->time.toSec() - waypointTimer > 1.3) 
                transition_to = AVOIDHOME_DRIVE;
            if(this->inputs->time.toSec() - initialTime > 5 && TagUtilities::hasTag(&this->inputs->tags, 256)){
                transition_to = AVOIDHOME_ESCAPE;
                initialTime = this->inputs->time.toSec();
            }
            break;
        }
        case AVOIDHOME_DRIVE:
        {
            if(abs(this->inputs->odom_accel_gps.theta) - abs(this->inputs->initialAvoidAngle) > 1){
                this->inputs->rotationFlag = true;
            }
            if(TagUtilities::hasTag(&this->inputs->tags , 256 ))
                transition_to = AVOIDHOME_INIT;
            initialTime = this->inputs->time.toSec();
            break;
        }
        case AVOIDHOME_ESCAPE:
        {
            if(this->inputs->time.toSec() - initialTime < 5 && this->inputs->time.toSec() - waypointTimer > 3){
                transition_to = AVOIDHOME_DRIVE;
            }
            break;
        }

    }

    return transition_to;
}

void AvoidHomeState::internalAction()
{
    RawOutputWaypoint *waypoint = 0;
    RawOutputParams params;
    this->waypoints.clear();
    switch( internal_state )
    {
        default: break;
        case AVOIDHOME_INIT:
        {
            wheelRatio = 1;
            params.left_output = -65;
            params.right_output = 65;
            params.duration = 1.5;
            if(TagUtilities::hasTag(&this->inputs->tags, 256))
                waypointTimer = this->inputs->time.toSec();
           break;
        }
        case AVOIDHOME_DRIVE:
        {
            params.left_output = 60 * wheelRatio;
            params.right_output = 60 * (1/wheelRatio);
            wheelRatio += 0.04;
            wheelRatio = min(wheelRatio, 4.3);
            waypointTimer = this->inputs->time.toSec();
            cout << "WHEEL RATIO: " << wheelRatio << endl;
            break;
        }
        case AVOIDHOME_ESCAPE:
        {
            params.left_output = 80;
            params.right_output = 80;
            params.duration = 3;
            cout << "----ESCAPE------" << endl;
            waypointTimer = this->inputs->time.toSec();
        }
    }
    waypoint = new RawOutputWaypoint( this->inputs, params );
    this->waypoints.push_back( dynamic_cast<Waypoint*>( waypoint ) );
    this->outputs->current_waypoint = waypoints.front();
            
}

void AvoidHomeState::forceTransition( InternalAvoidHomeState transition_to )
{
    InternalAvoidHomeState prev_state = internal_state;

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

double AvoidHomeState::getNearestUS (){
    cout << "L: " << this->inputs->us_left <<  "C: " << this->inputs->us_center <<  "R: " << this->inputs->us_right << endl;
    return min(min(this->inputs->us_left, this->inputs->us_right),this->inputs->us_center);
}
