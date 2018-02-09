#include "ReturnMachine.h"
#include "ReturnInit.h"
#include "ReturnDrive.h"

ReturnMachine::ReturnMachine( IOTable *io ) : SubMachine( io )
{
    ReturnInit *init = new ReturnInit();
    ReturnDrive *drive = new ReturnDrive();

    addState( init->getIdentifier(), (State *)init );
    addState( drive->getIdentifier(), (State *)drive );
}
