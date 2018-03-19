#include "FindHomeState.h"
#include "../TagUtilities.h"
#include "../waypoints/SimpleWaypoint.h"

void FindHomeState::action()
{
    forceTransition( internalTransition() );
    internalAction();
}

void FindHomeState::onEnter( std::string prev_state )
{
    if( this->internal_state == FINDHOME_COMPLETE )
    {
        if( waypoints.size() > 0 )
        {
            while( this->waypoints.front() )
            {
                Waypoint *wp = this->waypoints.front();
                this->waypoints.erase( waypoints.begin() );
                if( wp )
                    delete wp;
            }
        }
        forceTransition( FINDHOME_INIT );
    }
    else if( waypoints.size() > 0 )
    {
        outputs->current_waypoint = waypoints.front();
    }
}

void FindHomeState::onExit( std::string next_state )
{

}

std::string FindHomeState::transition()
{
    std::string transition_to = getIdentifier();

    if( TagUtilities::hasTag( &this->inputs->tags, 256 ) )
    {
        forceTransition( FINDHOME_COMPLETE );
        transition_to = "dropoff_state";
    }
    else if( TagUtilities::hasTag( &this->inputs->tags, 0 ) && !TagUtilities::hasTag(&this->inputs->tags, 256))
        transition_to = "avoidcube_state";
    else if( this->inputs->us_center < .4 || this->inputs->us_left < .4 ||  this->inputs->us_right < .4 )
        transition_to = "avoid_state";


    return transition_to;
}

FHState FindHomeState::internalTransition()
{
    FHState transition_to = internal_state;

    switch( internal_state )
    {
        default: break;
        case FINDHOME_INIT:
            if( this->waypoints.size() != 0 )
                transition_to = FINDHOME_GOHOME;
            break;
        case FINDHOME_GOHOME:
            if( this->waypoints.size() == 0 )
                transition_to = FINDHOME_LOST;
            break;
        case FINDHOME_LOST:
            if( this->waypoints.size() == 0 )
                transition_to = FINDHOME_INIT;
            break;
        case FINDHOME_COMPLETE:
            break;
        case FINDHOME_RESET:
            if( this->waypoints.size() != 0 )
                transition_to = FINDHOME_GOHOME;
            break;
    }

    return transition_to;
}

void FindHomeState::internalAction()
{
    switch( internal_state )
    {
        default: break;
        case FINDHOME_INIT:
        {
            SimpleWaypoint *waypoint;
            SimpleParams params;

            params.skid_steer_threshold = M_PI/12;
            params.arrived_threshold = 0.05;

            params.goal_x = 0.0;
            params.goal_y = 0.0;

            waypoint = new SimpleWaypoint( this->inputs, params );
            this->waypoints.push_back( dynamic_cast<Waypoint*>( waypoint ) );
            this->outputs->current_waypoint = waypoints.front();
            break;
        }
        case FINDHOME_GOHOME:
        case FINDHOME_LOST:
            /* both states should cycle through the waypoints */
            if( waypoints.size() > 0 )
            {
                Waypoint *waypoint = waypoints.front();
                if( waypoint && waypoint->hasArrived() )
                {
                    delete waypoint;
                    this->waypoints.erase( this->waypoints.begin() );
                    if( this->waypoints.size() > 0 )
                        this->outputs->current_waypoint = waypoints.front();
                    else
                        this->outputs->current_waypoint = 0;
                }
                break;
            }
            break;
        case FINDHOME_COMPLETE:
            break;
        case FINDHOME_RESET:
            break;
    }
}

void FindHomeState::forceTransition( FHState transition_to )
{
    FHState prev_state = internal_state;

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
            case FINDHOME_LOST:
            {
                SimpleWaypoint *waypoint = 0;
                SimpleParams params;
                double k = GROWTH_CONSTANT;
                double compX = this->inputs->odom_accel_gps.x;
                double compY = this->inputs->odom_accel_gps.y;
                double dot = 0;
                double x = 0;
                double y = 0;
                double distanceFromHome = hypot(compX, compY);

                /* param basics */
                params.arrived_threshold = 0.5;
                params.skid_steer_threshold = M_PI/12;

                compX /= distanceFromHome;
                compY /= distanceFromHome;

                for( double i = 0; i < 30; i += 0.5 )
                {
                    x = i * cos(i);
                    y = i * sin(i);

                    dot = (-1)*(x*compX + y*compY)/(hypot(x-compX,y-compY));
                    dot += 1.3;
                    dot /= 2;

                    params.goal_x = x * dot * k;
                    params.goal_y = y * dot * k;

                    waypoint = new SimpleWaypoint( this->inputs, params );
                    this->waypoints.push_back( (Waypoint *)waypoint );
                }
                this->outputs->current_waypoint = waypoints.front();
                break;
            }
            case FINDHOME_COMPLETE:
            {
                while( this->waypoints.size() > 0 )
                {
                    delete this->waypoints.front();
                    waypoints.erase( waypoints.begin() );
                }
                this->outputs->current_waypoint = 0;
                break;
            }
        }
    }
}
