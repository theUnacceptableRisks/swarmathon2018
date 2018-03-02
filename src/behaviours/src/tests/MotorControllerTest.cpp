#include "MotorController.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <math.h>

int main()
{
    MotorController controller( 15 );
    MotorParams params;

    /* Linear Tests */
    std::cout << "************ Starting Linear Tests ************" << std::endl;
    params.dist_deccel_point = 2.50;
    params.dist_max_output = 25;
    params.dist_goal = 0.0;

    params.dist_current = 5.0;
    while( params.dist_current > 0 )
    {
        std::tuple<int,int> output = controller.generateLinearOutput( params );
        std::cout << "Error: " << (params.dist_current) << "\tOutputs: " << std::get<0>( output ) << " " << std::get<1>( output ) << std::endl;
        params.dist_current -= 0.1;
    }

    /* Rotational Tests */
    std::cout << "************ Starting Rotational Tests ************" << std::endl;
    params.yaw_deccel_point = M_PI_4;
    params.yaw_max_output = 15;
    params.yaw_goal = M_PI_2;

    params.yaw_current = 0;
    while( params.yaw_current < M_PI_2 )
    {
        std::tuple<int,int> output = controller.generateRotationalOutput( params );
        std::cout << "Error: " << params.yaw_current << "\tOutputs: " << std::get<0>( output ) << " " << std::get<1>( output ) << std::endl;
        params.yaw_current += 0.05;
    }

    params.yaw_goal = M_PI;
    while( params.yaw_current < M_PI )
    {
        std::tuple<int,int> output = controller.generateRotationalOutput( params );
        std::cout << "Error: " << params.yaw_current << "\tOutputs: " << std::get<0>( output ) << " " << std::get<1>( output ) << std::endl;
        params.yaw_current += 0.05;
    }

    params.yaw_goal = 0;
    while( params.yaw_current > 0 )
    {
        std::tuple<int,int> output = controller.generateRotationalOutput( params );
        std::cout << "Error: " << params.yaw_current << "\tOutputs: " << std::get<0>( output ) << " " << std::get<1>( output ) << std::endl;
        params.yaw_current -= 0.05;
    }

    /* Skid Tests */
    std::cout << "************ Starting Skid Tests ************" << std::endl;
    params.yaw_goal = M_PI_2;

    params.yaw_current = 0;
    params.dist_current = 5.0;

    while( params.yaw_current < M_PI_2 || params.dist_current > 0 )
    {
        std::tuple<int,int> output = controller.generateSkidOutput( params );
        std::cout << "Dist Error: " << params.dist_current << "\tYaw Error: " << params.yaw_current << "\tOutputs: " << std::get<0>( output ) << " " << std::get<1>( output ) << std::endl;
        if( params.yaw_current < M_PI_2 )
            params.yaw_current += 0.05;
        if( params.dist_current > 0 )
            params.dist_current -= 0.1;
    }

    return 0;
}
