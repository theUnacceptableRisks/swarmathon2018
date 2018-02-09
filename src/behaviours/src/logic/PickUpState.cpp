#include "PickUpState.h"

void PickUpState::action()
{
//    pickup_machine.run();
}

std::string PickUpState::transition()
{
    std::string transition_to = "dropoff_state";
    return transition_to;
}
