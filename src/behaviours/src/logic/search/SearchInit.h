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
                WaypointUtilities::DrivingParams params;
                SimpleWaypointSupplementalInputs s_params;

                params.goal_x = -2.0;
                params.goal_y = 0;
                params.current_x = &ssm_owner->inputs->odom_accel.x;
                params.current_y = &ssm_owner->inputs->odom_accel.y;
                params.current_theta = &ssm_owner->inputs->odom_accel.theta;
                params.current_linear_vel = &ssm_owner->inputs->linear_vel_odom_accel;
                params.current_angular_vel = &ssm_owner->inputs->angular_vel_odom_accel;

                s_params.odom_x = &ssm_owner->inputs->raw_odom.x;
                s_params.odom_y = &ssm_owner->inputs->raw_odom.y;

                SimpleWaypoint *waypoint = new SimpleWaypoint( params, s_params );
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
