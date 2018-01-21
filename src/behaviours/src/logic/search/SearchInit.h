#ifndef searchinit_h
#define searchinit_h

#include "SearchStateBase.h"
#include "../../waypoints/WaypointUtilities.h"

class SearchInit : public SearchStateBase
{
    public:
        SearchInit() : SearchStateBase( "search_init" ), setup_complete(false) {}
        virtual void action()
        {
            if( ssm_owner )
            {
                SimpleWaypoint *waypoint = 0;
                SimpleParams params;
                double x = 0;
                double y = 0;

                params.skid_steer_threshold = 0.15;
                for( double n = 1.0; n < 10; n += 1.0 )
                {
                    y += n * pow( (-1.0), ( n + 1.0 ) );
                    params.goal_x = x;
                    params.goal_y = y;
                    waypoint = new SimpleWaypoint( ssm_owner->inputs, params );
                    ssm_owner->waypoints.push_back( (Waypoint *)waypoint );

                    x += ( n + 1.0 ) * pow( (-1.0), ( n + 1.0 ) );
                    params.goal_x = x;
                    params.goal_y = y;
                    waypoint = new SimpleWaypoint( ssm_owner->inputs, params );
                    ssm_owner->waypoints.push_back( (Waypoint *)waypoint );
                }

                setup_complete = true;
            }

        }
        virtual std::string transition()
        {
            std::string transition_to = getIdentifier();

            if( setup_complete )
                transition_to = "search_drive";

            return transition_to;
        }
    private:
        bool setup_complete;
};

#endif
