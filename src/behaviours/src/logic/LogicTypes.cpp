#include "LogicTypes.h"

bool shouldAvoidCube( LogicInputs *inputs )
{
    bool should_avoid = false;

    if( inputs->cubes.size() > 0 )
    {
        if( inputs->cubes.size() == 1 )
        {
            Cube cube = inputs->cubes.at(0);
            double cube_x = cube.getPositionX();

            if( cube.getDistance() < 0.20 && ( cube_x > -0.05 && cube_x < 0.05 ) )
                should_avoid = false;
        }
        else
        {
            Cube cube = TagUtilities::getSecondClosestCube( &inputs->cubes );
            if( cube.getDistance() < 0.4 )
                should_avoid = true;
        }
    }

    return should_avoid;
}
