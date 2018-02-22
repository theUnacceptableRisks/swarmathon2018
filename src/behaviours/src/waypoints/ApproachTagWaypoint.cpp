#include "ApproachTagWaypoint.h"

void ApproachTagWaypoint::run()
{
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int> ( 0, 0 );

    if( this->has_arrived == false )
    {
        if( TagUtilities::hasTag( &inputs->tags, this->desired_tag_id ) )
        {
            Tag current_tag = inputs->tags.back();
            double current_distance = TagUtilities::getDistance( current_tag );

            if( current_distance <= this->desired_distance )
                has_arrived = true;
            else
            {
                MotorParams m_params;

                m_params.dist_deccel_point = 0.05;
                m_params.dist_current = current_distance;
                m_params.dist_goal = this->desired_distance;
                m_params.dist_max_output = 10;

                m_params.yaw_deccel_point = .1;
                m_params.yaw_current = current_tag.getPositionX();
                m_params.yaw_goal = 0.0;
                m_params.yaw_max_output = 10;

                leftAndRight = inputs->controller.generateSkidOutput( m_params );

                setOutputLeftPWM( std::get<0>( leftAndRight ) );
                setOutputRightPWM( std::get<1>( leftAndRight ) );

             }
        }
        else
        {
            /* need to start counting failures here */
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
