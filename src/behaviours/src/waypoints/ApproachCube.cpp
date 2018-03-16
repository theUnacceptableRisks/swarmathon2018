#include "ApproachCube.h"

void ApproachCube::run()
{
    if( this->has_arrived == false )
    {
        if( inputs->cubes.size() > 0 )
        {
            double current_distance = TagUtilities::getClosestCube( &inputs->cubes );
        }
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
