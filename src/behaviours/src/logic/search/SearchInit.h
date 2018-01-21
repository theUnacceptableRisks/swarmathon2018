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
                SimpleParams params;
                params.goal_x = -2.0;
                params.goal_y = 0.0;

                SimpleWaypoint *waypoint = new SimpleWaypoint( ssm_owner->inputs, params );
                ssm_owner->waypoints.push_back( (Waypoint *)waypoint );

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
