#ifndef waypoint_h
#define waypoint_h

class Waypoint
{
    public:
        float getOutputLinearVelocity() { return output_linear_velocity; }
        float getOutputAngularVelocity() { return output_angular_velocity; }
    protected:
        void setOutputLinearVelocity( float vel ) { output_linear_velocity = vel; }
        void setOutputAngularVelocity( float vel ) { output_angular_velocity = vel; }
    private:
        float output_linear_velocity;
        float output_angular_velocity;
};

#endif
