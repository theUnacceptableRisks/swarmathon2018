#include "PID.h"

PID::PID() {   }

PID::PID(PIDConfig config)
{
  this->config = config;
}

double PID::PIDOut( double current, double goal)
{
    double P = 0.;
    double I = 0.;
    double D = 0.;
    double current_error = current - goal;
    double integ_error = 0.0;


    std::cout << "current error: " << current_error << std::endl;

    if( fabs( current_error ) < config.start_integrating && fabs( current_error ) > config.integ_limit )
    {
        if( sum_error.size() > config.max_error_history )
        {
            sum_error.pop_back();
            sum_error.insert( sum_error.begin(), current_error );
        }
        else
            sum_error.insert( sum_error.begin(), current_error );
    }
    else
        sum_error.clear();

    if( goal != prev_set_point )
        resetPID();

    prev_set_point = goal;

    P = current_error * config.Kp;

    /* don't sum the error if we dont have Ki or sum_error vector is zero */
    if( config.Ki > 0 && sum_error.size() > 0 )
    {
        for( int x = 0; x < sum_error.size(); x++ )
            integ_error += sum_error[x];
        I = integ_error * config.Ki;
    }

    D = ( current_error - prev_error ) * config.Kd;

//    std::cout << "current measurement " << current << std::endl;
//    std::cout << "goal " << goal << std::endl;
      std::cout << "P " << P << std::endl;
      std::cout << "I " << I << std::endl;
//    std::cout << "D " << D << std::endl;

    prev_error = current_error;

    return ( P + I + D );
}

void PID::resetPID()
{
    prev_error = 0;
    sum_error.clear();
}
