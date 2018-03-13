#ifndef pid_h
#define pid_h

#include <tuple>
#include <vector>

#define DERIV_MAX 5	/* the lower this number the more sensitive to sudden and rapid change the PID will be */
#define INTEG_MAX 50	/* the higher this number, the more error is summed. This will lead to higher I term outputs */

typedef struct pid_params
{
    double Kp = 60.;
    double Ki = 0.;
    double Kd = 0.;
    double integration_point = 0.;
    bool radians_mode = false;
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
        PID() : prev_error(0), prev_time(0), params(PidParams()) {}
        PID( PidParams p ) : prev_error(0), prev_time(0), params(p) {}
        int execute( PidInputs inputs );
        void setParams( PidParams new_params );
        void reset();
    private:
        void addDerivative( double value );
        void addIntegral( double value );
        double getErrorDerivative();
        double getErrorIntegral();

        PidParams params;
        std::vector<double> error_derivative;
        std::vector<double> error_integral;
        double prev_goal;
        double prev_error;
        double prev_time;
};

#endif
