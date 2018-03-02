#ifndef motorcontroller_h
#define motorcontroller_h

#include <tuple>
#include <math.h>

typedef struct motor_params
{
    double dist_deccel_point = 0.0;
    double dist_current = 0.0;
    double dist_goal = 0.0;
    int dist_max_output = 0;

    double yaw_deccel_point = 0.0;
    double yaw_current = 0.0;
    double yaw_goal = 0.0;
    bool yaw_in_radians = false;
    int yaw_max_output = 0;
} MotorParams;

typedef enum
{
    LINEAR, ROTATE, SKID
} DriveType;

class MotorController
{
    public:
        MotorController() : min_motor_output(0) {}
        MotorController( int mmo ) : min_motor_output(mmo) {}
        std::tuple<int,int> generateLinearOutput( MotorParams params );
        std::tuple<int,int> generateRotationalOutput( MotorParams params );
        std::tuple<int,int> generateSkidOutput( MotorParams params );
        void changeMotorMin( int new_min );
    private:
        double calcKonstant( int max, double deccel );
        int getOutput( double error, double konstant );
        int min_motor_output;
};


#endif
