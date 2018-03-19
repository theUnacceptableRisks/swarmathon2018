#include "ApproachCube.h"

void ApproachCube::run()
{
    /* if we've arrived, don't do anything */
    if( this->has_arrived == false )
    {
        /* if there aren't cubes, don't do anything */
        if( inputs->cubes.size() > 0 )
        {
            Cube closest = TagUtilities::getClosestCube( &inputs->cubes );
            double distance = closest.getDistance();

            /* now let's get down to business, check to see if we've arrived */
            if( distance <= this->c_params.dist_goal )
            {
                this->has_arrived = true;
                setOutputLeftPWM( 0 );
                setOutputRightPWM( 0 );
            }
            else
            {
                PidInputs pid_inputs;
                std::tuple<int,int> linear_output;
                std::tuple<int,int> rotational_output;
                double x_position = 0;

                /* if we haven't arrived, it's time to do the work to try and arrive */

                if( distance <= OPTIMAL_LOCK_DISTANCE )
                {
                    /* close enough where we shouldn't lose the cube, just approach the closest */
                    x_position = closest.getPositionX();
                }
                else
                {
                    /* average Xs of all cubes */
                    int num_cubes = inputs->cubes.size();

                    for( int i = 0; i < num_cubes; i++ )
                        x_position += inputs->cubes.at(i).getPositionX();

                    x_position /= num_cubes;

                }

                pid_inputs.measured = x_position;
                pid_inputs.goal = c_params.yaw_goal;
                pid_inputs.time = inputs->time.toSec();
                pid_inputs.saturation = c_params.yaw_max_output;

                rotational_output = linear_rot_pid.execute( pid_inputs );

                /* does rotation only, quick hack that shouldn't be used anymore */
                if( distance <= OPTIMAL_LOCK_DISTANCE && fabs( x_position ) > c_params.skid_rotate_threshold )
                {
                    linear_output = std::make_tuple( 0, 0 );
                }
                else
                {
                    pid_inputs.measured = distance;
                    pid_inputs.goal = c_params.dist_goal;
                    pid_inputs.time = inputs->time.toSec();
                    pid_inputs.saturation = c_params.dist_max_output;

                    linear_output = linear_pid.execute( pid_inputs );
                }

                setOutputLeftPWM( std::get<0>(linear_output) + std::get<0>(rotational_output ) );
                setOutputRightPWM( std::get<1>(linear_output) + std::get<1>(rotational_output ) );
            }
        }
        else
        {
            setOutputLeftPWM( 0 );
            setOutputRightPWM( 0 );
        }
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
