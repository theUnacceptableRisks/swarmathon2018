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
            double x_position = 0;
            std::tuple<int,int> linear_output;
            std::tuple<int,int> rotational_output;


            if( distance >= OPTIMAL_LOCK_DISTANCE )
            {
                PidInputs pid_inputs;

                /* average */
                int num_cubes = inputs->cubes.size();

                for( int i = 0; i < num_cubes; i++ )
                    x_position += inputs->cubes.at(i).getPositionX();

                x_position /= num_cubes;

                /* rotational first, no specific reason */

                pid_inputs.measured = x_position;
                pid_inputs.goal = c_params.yaw_goal;
                pid_inputs.time = inputs->time.toSec();
                pid_inputs.max_output = c_params.yaw_max_output;

                rotational_output = linear_rot_pid.execute( pid_inputs );

                /* linear second */
                pid_inputs.measured = distance;
                pid_inputs.goal = c_params.dist_goal;
                pid_inputs.time = inputs->time.toSec();
                pid_inputs.max_output = c_params.dist_max_output;

                linear_output = linear_pid.execute( pid_inputs );
            }
            else if( distance >= c_params.dist_goal )
            {
                PidInputs pid_inputs;

                x_position = closest.getPositionX();

                /* rotational first, no specific reason */

                pid_inputs.measured = x_position;
                if( pid_inputs.measured >= 0 )
                    pid_inputs.goal = CAMERA_OFFSET*2;
                else
                    pid_inputs.goal = 0.023;
                pid_inputs.time = inputs->time.toSec();
                pid_inputs.max_output = c_params.yaw_max_output;

                rotational_output = linear_rot_pid.execute( pid_inputs );

                /* linear second */
                pid_inputs.measured = distance;
                pid_inputs.goal = c_params.dist_goal;
                pid_inputs.time = inputs->time.toSec();
                pid_inputs.max_output = c_params.dist_max_output;

                linear_output = linear_pid.execute( pid_inputs );
            }
            else
            {
/*                std::cout << "Final Rotation" << std::endl;
                PidInputs pid_inputs;

                x_position = closest.getPositionX();
                if( fabs( c_params.yaw_goal - x_position ) > 0.002 )
                {
                    pid_inputs.measured = x_position;
                    pid_inputs.goal = c_params.yaw_goal;
                    pid_inputs.time = inputs->time.toSec();
                    pid_inputs.max_output = c_params.yaw_max_output;

                    linear_output = std::make_tuple( 0, 0 );
                    rotational_output = final_rot_pid.execute( pid_inputs );
                }
                else
                { */
                    has_arrived = true;
                    linear_output = std::make_tuple( 0, 0 );
                    rotational_output = std::make_tuple( 0, 0 );
               // }
            }
            setOutputLeftPWM( std::get<0>(linear_output) + std::get<0>(rotational_output ) );
            setOutputRightPWM( std::get<1>(linear_output) + std::get<1>(rotational_output ) );
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
