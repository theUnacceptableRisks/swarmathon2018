#include "PickUpMachine.h"
#include "PickUpApproach.h"

PickUpMachine::PickUpMachine( IOTable *io ) : SubMachine( io )
{
    //init/add states
    PickUpApproach *approach = new PickUpApproach();

    addState( approach->getIdentifier(), dynamic_cast<State*>( approach ) );
}
