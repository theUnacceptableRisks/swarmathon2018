#include <iostream>
#include "OliverPickUpState.h"
#include "../TagUtilities.h"
#include "../waypoints/RawOutputWaypoint.h"

void OliverPickUpState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void OliverPickUpState::onEnter( std::string prev_state )
{
    previousState = prev_state;
    if( waypoints.size() > 0 )
        outputs->current_waypoint = waypoints.front();
    initialTheta = this->inputs->odom_accel_gps.theta;
}

void OliverPickUpState::onExit( std::string next_state )
{

}

std::string OliverPickUpState::transition()
{
    std::string transition_to = getIdentifier();

    return transition_to;
}

InternalOliverPickUpState OliverPickUpState::internalTransition()
{
    InternalOliverPickUpState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case OLIVERPICKUP_INIT:
            //if(!TagUtilities::hasTag(&this->inputs->tags , 0 ))
                //transition_to = OLIVERPICKUP_DRIVE;
            break;
        case OLIVERPICKUP_DRIVE:
            if(TagUtilities::hasTag(&this->inputs->tags , 0 ))
                transition_to = OLIVERPICKUP_INIT;
            break;
    }

    return transition_to;
}

void OliverPickUpState::internalAction()
{
    RawOutputWaypoint *waypoint = 0;
    RawOutputParams params;
    this->waypoints.clear();
    switch( internal_state )
    {
        default: break;
        case OLIVERPICKUP_INIT:
        {
            if(TagUtilities::hasTag(&this->inputs->tags , 0 )){
                
            params.left_output = 60 * (-.02 - TagUtilities::getClosestTag(&this->inputs->tags, 0).getPositionX()) * damper;
            params.left_output = -60 * (-.02 - TagUtilities::getClosestTag(&this->inputs->tags, 0).getPositionX()) * damper;
            damper *= (-.02 - TagUtilities::getClosestTag(&this->inputs->tags, 0).getPositionX()) + .9;
            std::cout << (-.02 - TagUtilities::getClosestTag(&this->inputs->tags, 0).getPositionX()) << endl;
            }
            break;
        }
        case OLIVERPICKUP_DRIVE:
        {
            params.left_output = 0 * wheelRatio;
            params.right_output = 0 * (1/wheelRatio);
            wheelRatio += 0.04;
            break;
        }
    }
    std::cout << "PICKUP INIT" << endl;
    if(TagUtilities::hasTag(&this->inputs->tags , 0 ))
    waypoint = new RawOutputWaypoint( this->inputs, params );
    this->waypoints.push_back( dynamic_cast<Waypoint*>( waypoint ) );
    this->outputs->current_waypoint = waypoints.front();
            
}

void OliverPickUpState::forceTransition( InternalOliverPickUpState transition_to )
{
    InternalOliverPickUpState prev_state = internal_state;

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

double OliverPickUpState::getNearestUS (){
    cout << "L: " << this->inputs->us_left <<  "C: " << this->inputs->us_center <<  "R: " << this->inputs->us_right << endl;
    return min(min(this->inputs->us_left, this->inputs->us_right),this->inputs->us_center);
}
