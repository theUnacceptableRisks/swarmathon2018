#include "SearchMachine.h"
#include "SearchInit.h"
#include "SearchDrive.h"

SearchMachine::SearchMachine( IOTable *io ) : SubMachine( io )
{
    SearchInit *init = new SearchInit();
    SearchDrive *drive = new SearchDrive();

    addState( init->getIdentifier(), (State *)init );
    addState( drive->getIdentifier(), (State *)drive );
}
