#ifndef pickupmachine_h
#define pickupmachine_h

#include "../SubMachine.h"

class PickUpMachine : public SubMachine
{
    friend class PickUpApproach;
    public:
        PickUpMachine( IOTable *io );
    private:
};

#endif
