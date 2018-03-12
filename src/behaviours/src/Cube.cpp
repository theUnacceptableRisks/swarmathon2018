#include "Cube.h"

Cube::Cube( Tag init_tag )
{
    tags.push_back( init_tag );
}

bool Cube::checkTag( Tag tag )
{
    bool same_cube = false;

    for( int i = 0; i < this->tags.size(); i++ )
    {
        Tag &cur_tag = tags.at(i);
        if( fabs( tag.getPositionX() - cur_tag.getPositionX() ) < CUBE_TOLERANCE &&
            fabs( tag.getPositionY() - cur_tag.getPositionY() ) < CUBE_TOLERANCE &&
            fabs( tag.getPositionZ() - cur_tag.getPositionZ() ) < CUBE_TOLERANCE )
        {
            same_cube = true;
            this->tags.push_back( tag );
        }
        if( same_cube )
            break;
    }
    return same_cube;
}
