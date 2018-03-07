#include "Waypoint.h"

Waypoint::Waypoint( LogicInputs *i ) : StateMachine(), inputs(i), has_arrived(false), output_left_pwm(0), output_right_pwm(0)
{
}

bool Waypoint::hasArrived( void )
{
    return has_arrived;
}

std::tuple<int,int> Waypoint::getOutput()
{
    return std::make_tuple( output_left_pwm, output_right_pwm );
}

void Waypoint::setOutputLeftPWM( int pwm )
{
    output_left_pwm = pwm;
}
void Waypoint::setOutputRightPWM( int pwm )
{
    output_right_pwm = pwm;
}

