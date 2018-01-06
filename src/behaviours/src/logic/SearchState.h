#include "../state_machine/State.h"
#include "LogicMachine.h"

class SearchState : public State
{
   public:
       SearchState() : State ( "search_state" ), ss_owner(0) {}
       virtual bool setOwner( StateMachine *sm );

   private:
       LogicMachine *ss_owner;

};
