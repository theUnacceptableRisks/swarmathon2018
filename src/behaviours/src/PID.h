#ifndef pid_h
#define pid_h

#include <tuple>
#include <vector>
#include <cmath>

#define DERIV_MAX 5	/* the lower this number the more sensitive to sudden and rapid change the PID will be */
#define INTEG_MAX 1000	/* the higher this number, the more error is summed. This will lead to higher I term outputs */

typedef struct pid_params
{
    int bias = 20;
    double Kp = 60.;
    double Ki = 0.;
    double Kd = 0.;
    double integration_point = 0.;
} PidParams;

typedef struct pid_inputs
{
    double measured;
    double goal;
    double time;
    int max_output;
} PidInputs;

class PID
{
    public:
        PID() : prev_error(0), prev_time(0), error_inf(0), params(PidParams()) {}
        PID( PidParams p ) : prev_error(0), prev_time(0), params(p), error_inf(0) {}
        virtual std::tuple<int,int> execute( PidInputs inputs ) { return std::make_tuple( 0, 0 ); }
        void setParams( PidParams new_params );
        void reset();
    protected:
        int runPID( double error, double dt );
        void addIntegral( double value );
        double getErrorIntegral();

        PidParams params;
        std::vector<double> error_derivative;
        std::vector<double> error_integral;
        double error_inf;
        double prev_goal;
        double prev_error;
        double prev_time;
};

#endif
