#include "WaypointUtilities.h"


float WaypointUtilities::getDistance( DrivingParams params )
{
    //simple hypotenuse of the difference between the two points
    //order shouldnt matter as long as its consistant
    return hypot( fabs( params.goal_x - params.current_x ),
                  fabs( params.goal_y - params.current_y ) );
}

float WaypointUtilities::getAngularCorrectionNeeded( DrivingParams params )
{
    //goal_theta -> tan = opposite/adjacent, ie this gives us an angular heading we need to be on to reach out destination
    //shortest_angular_distance finds the smaller of the two amounts we could rotate in either direction to arrive there

    float goal_theta = atan2( ( params.goal_y - params.current_y ), ( params.goal_x - params.current_x ) );

    return angles::shortest_angular_distance( params.current_theta, goal_theta );
}
