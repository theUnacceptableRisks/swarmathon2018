#include "ApproachHome.h"

void ApproachHome::run()
{
    if( this->has_arrived == false )
    {
        if( TagUtilities::hasTag( &inputs->tags, 256 ) && inputs->tags.size() > 0 )
        {
            Tag closest = TagUtilities::getClosestTag( &inputs->tags, 256 );
            double distance = TagUtilities::getDistance( closest );

            if( distance <= this->h_params.dist_goal )
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
                double x_measured = 0.;
                double count;

                for( int i = 0; i < inputs->tags.size(); i++ )
                {
                    Tag curr_tag = inputs->tags.at(i);
                    if( curr_tag.getID() == 256 )
                    {
                        x_measured += curr_tag.getPositionX();
                        count++;
                    }
                }
                x_measured /= count;

                pid_inputs.measured = x_measured;
                pid_inputs.goal = h_params.yaw_goal;
                pid_inputs.time = inputs->time.toSec();
                pid_inputs.max_output = h_params.yaw_max_output;

                rotational_output = linear_rot_pid.execute( pid_inputs );

                pid_inputs.measured = distance;
                pid_inputs.goal = h_params.dist_goal;
                pid_inputs.time = inputs->time.toSec();
                pid_inputs.max_output = h_params.dist_max_output;

                linear_output = linear_pid.execute( pid_inputs );

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

