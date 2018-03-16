#ifndef linearpid_h
#define linearpid_h

#include "PID.h"

class LinearPID : public PID
{
    public:
        LinearPID() : PID() {}
        LinearPID( PidParams P ) : PID( P ) {}
        virtual std::tuple<int,int> execute( PidInputs inputs );
};

#endif
