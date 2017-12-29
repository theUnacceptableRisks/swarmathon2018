#include <vector>
#include "../state_machine/IOType.h"
#include "../Tag.h"

//need to do some permissions work on this one

class InputTags : public IOType
{
    public:
        InputTags( std::vector<Tag> *t ) : IOType( IO_TAGS, TAG_SUM, sizeof( InputTags ) ),
            tags(t) {}
        std::vector<Tag> *tags;
};

VALIDATOR iotags_validator = { IO_TAGS, sizeof( InputTags ), TAG_SUM };
