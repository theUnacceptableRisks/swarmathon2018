#include <math.h>
#include <angles/angles.h>

namespace WaypointUtilities
{
    typedef struct standard_driving_params
    {
        const float goal_x;
        const float goal_y;
        const float current_x;
        const float current_y;
        const float current_theta;
    } DrivingParams;

    float getDistance( DrivingParams params );
    float getAngularCorrectionNeeded( DrivingParams params );

};
