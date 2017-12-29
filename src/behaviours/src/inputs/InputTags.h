#ifndef inputtags_h
#define inputtags_h

#include <vector>
#include "../state_machine/IOType.h"
#include "../Tag.h"

//need to do some permissions work on this one

class InputTags : public IOType
{
    public:
        InputTags( std::vector<Tag> *t ) : IOType( ROVER_IO.TAGS, ROVER_SUM.TAG, sizeof( InputTags ) ),
            tags(t) {}
        std::vector<Tag> *tags;
};

VALIDATOR iotags_validator = { ROVER_IO.TAGS, sizeof( InputTags ), ROVER_SUM.TAG };

#endif
