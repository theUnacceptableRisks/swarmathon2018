#include "LinearWaypoint.h"

void LinearWaypoint::run()
{
    std::tuple<int,int> output;
    double current_distance = fabs( this->original_x - this->inputs->raw_odom.x );

    if( current_distance >= l_params.distance )
        this->has_arrived = true;

    if( this->has_arrived == false )
    {
        MotorParams m_params;

        m_params.dist_deccel_point = l_params.deccel_point;
        m_params.dist_current = l_params.distance - current_distance;
        if( this->l_params.reverse )
            m_params.dist_current *= -1;
        m_params.dist_goal = 0;
        m_params.dist_max_output = l_params.max_vel;

        output = this->inputs->controller.generateLinearOutput( m_params );

        setOutputLeftPWM( std::get<0>( output ) );
        setOutputRightPWM( std::get<1>( output ) );
    }
    else
    {
        setOutputLeftPWM( 0 );
        setOutputRightPWM( 0 );
    }
}
