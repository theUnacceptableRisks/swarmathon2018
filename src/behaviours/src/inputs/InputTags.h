#ifndef inputtags_h
#define inputtags_h

#include <vector>
#include "../state_machine/IOType.h"
#include "../Tag.h"

//need to do some permissions work on this one

class InputTags : public IOType
{
    public:
        InputTags( std::vector<Tag> *t ) : IOType( IOTYPE_TAGS, SUM_TAG, sizeof( InputTags ) ),
            tags(t) {}
        std::vector<Tag> *tags;
};

extern VALIDATOR iotags_validator;

#endif
 
