#ifndef searchinit_h
#define searchinit_h

#include "SearchStateBase.h"

class SearchInit : public SearchStateBase
{
    public:
        SearchInit() : SearchStateBase( "search_init" )
        {
            WaypointUtilities::DrivingParams params;
            params.goal_x = -2.0;
            params.goal_y = 0;
            params.current_x = &ssm_owner->inputs.odom_accel.x;
            params.current_y = &ssm_owner->inputs.odom_accel.y;
            params.current_theta = &ssm_owner->inputs.odom_accel.theta;
            params.current_linear_vel = &ssm_owner->inputs.linear_vel_odom_accel;
            params.current_angular_vel = &ssm_owner->inputs.angular_vel_odom_accel;
            ssm_owner->waypoints.push_back();
        }
        virtual void transition()
        {
            return "search_drive";
        }
}

#endif
