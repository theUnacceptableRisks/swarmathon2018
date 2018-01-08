#ifndef waypoint_h
#define waypoint_h

#include "../state_machine/StateMachine.h"
#include <tuple>

class Waypoint : public StateMachine
{
    public:
        Waypoint() : has_arrived(false), output_left_pwm(0), output_right_pwm(0) {}

        bool hasArrived( void ) { return has_arrived; }

        std::tuple<float,float> getOutput()
        {
            return std::make_tuple( output_left_pwm, output_right_pwm );
        }
    protected:
        void setOutputLeftPWM( int pwm ) { output_left_pwm = pwm; }
        void setOutputRightPWM( int pwm ) { output_right_pwm = pwm; }
    private:
        bool has_arrived;
        int output_left_pwm;
        int output_right_pwm;
};

#endif