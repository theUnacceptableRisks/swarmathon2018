#ifndef returnmachine_h
#define returnmachine_h

#include "../SubMachine.h"

class ReturnMachine : public SubMachine
{
    friend class ReturnInit;
    friend class ReturnDrive;
    public:
        SearchMachine( IOTable *io );
};

#endif
