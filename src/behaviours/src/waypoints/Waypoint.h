#ifndef waypoint_h
#define waypoint_h

#include "WaypointUtilities.h"
#include "../state_machine/StateMachine.h"
#include "../logic/LogicTypes.h"
#include <tuple>

class Waypoint : public StateMachine
{
    public:
        Waypoint( LogicInputs *i );
        bool hasArrived( void );
        std::tuple<int,int> getOutput();
    protected:
        void setOutputLeftPWM( int pwm );
        void setOutputRightPWM( int pwm );
        WaypointUtilities::PidPackage pids;
        LogicInputs *inputs;
        bool has_arrived;
    private:
        int output_left_pwm;
        int output_right_pwm;
};

#endif
