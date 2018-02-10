#ifndef PID_H
#define PID_H

#include <vector>
#include <ros/ros.h>

using namespace std;

struct PIDConfig {
    double Kp = 0;
    double Ki = 0;
    double Kd = 0;
    double start_integrating = 0.0;
    double max_error_history = 10;
    double integ_limit = 0.02;
};

class PID
{
    public:
        PID();
        PID(PIDConfig config);

        double PIDOut(double current, double goal);
        void resetPID();

        void SetConfiguration(PIDConfig config) {this->config = config;}
    private:
        PIDConfig config;
        std::vector<double> sum_error;
        double prev_error = 0.0;
        double prev_set_point = 0.0;
};

#endif // PID_H
