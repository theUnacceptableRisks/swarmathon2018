#ifndef pid_h
#define pid_h

#include <tuple>
#include <vector>

#define DERIV_MAX 20
#define INTEG_MAX 20

typedef struct pid_params
{
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
        double prev_error;
        double prev_time;
};

#endif
