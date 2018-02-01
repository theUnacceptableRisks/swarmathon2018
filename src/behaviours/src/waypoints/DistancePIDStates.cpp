#include "DistancePIDStates.h"
#include "DistancePID.h"

void DistancePIDDrive::action()
{
    DistancePID *dps_owner = dynamic_cast<DistancePID*> ( owner );

    WaypointUtilities::PidParams wp_params;

    std::tuple<int,int> leftAndRight = std::make_tuple<int,int>( 0, 0 );

    if( dps_owner )
    {
        wp_params.velocity_error = WaypointUtilities::getDistance( dps_owner->driving_params );
        wp_params.velocity_goal = 1.0;
        wp_params.saturation_point = 60;

        leftAndRight = WaypointUtilities::executePid( wp_params, dps_owner->pids );

        dps_owner->setOutputLeftPWM( std::get<0>( leftAndRight ) );
        dps_owner->setOutputRightPWM( std::get<1>( leftAndRight ) );
    }
}
