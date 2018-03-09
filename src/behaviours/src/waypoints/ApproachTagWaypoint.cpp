#include "ApproachTagWaypoint.h"

void ApproachTagWaypoint::run()
{
    std::tuple<int,int> leftAndRight = std::make_tuple<int,int> ( 0, 0 );

    if( this->has_arrived == false )
    {
        if( TagUtilities::hasTag( &inputs->tags, this->t_params.desired_tag) )
        {
            Tag current_tag;

            /* approach the closest tag or the farthest tag */
            if( t_params.type == CLOSEST )
                current_tag = TagUtilities::getClosestTagSane( &inputs->tags, 0, 0.05 );
            else if( t_params.type == FARTHEST )
                current_tag = inputs->tags.front();
            else
                current_tag = TagUtilities::getClosestTag( &inputs->tags, 0 );

            /* check the distance */
            double current_distance = TagUtilities::getDistance( current_tag );

            if( prev_distance == 0 )
                prev_distance = current_distance;
            else
            {
                if( prev_distance - current_distance < 0.05 )
                {
                    return;
                }
            }
                /* is it below or at our goal */
            if( current_distance <= this->t_params.dist_goal )
                has_arrived = true;
            else
            {
                MotorParams m_params;

                if( fabs( current_tag.getPositionX() ) > this->t_params.skid_rotate_threshold )
                {
                    m_params.yaw_deccel_point = this->t_params.yaw_deccel;
                    m_params.yaw_current = current_tag.getPositionX();
                    m_params.yaw_goal = this->t_params.yaw_goal;
                    m_params.yaw_max_output = this->t_params.yaw_max_output;

                    leftAndRight = inputs->controller.generateRotationalOutput( m_params );
                }
                else
                {
                    m_params.dist_deccel_point = this->t_params.dist_deccel;
                    m_params.dist_current = current_distance;
                    m_params.dist_goal = this->t_params.dist_goal;
                    m_params.dist_max_output = this->t_params.dist_max_output;

                    leftAndRight = inputs->controller.generateLinearOutput( m_params );
                }
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
