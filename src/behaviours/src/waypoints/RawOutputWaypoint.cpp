#include "RawOutputWaypoint.h"

void RawOutputWaypoint::run()
{
    std::tuple<int,int> leftAndRight = std::make_tuple( 0, 0 );

    if( !this->has_arrived )
    {
        if( this->r_params.duration != 0 && ( this->inputs->time.toSec() - start_time ) > this->r_params.duration )
            this->has_arrived = true;
        else
        {
            leftAndRight = std::make_tuple( this->r_params.left_output, this->r_params.right_output );
        }
    }

    setOutputLeftPWM( std::get<0>( leftAndRight ) );
    setOutputRightPWM( std::get<1>( leftAndRight ) );
}
