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

double Cube::getPositionX()
{
    double x = 0.0;
    int size = tags.size();

    for( int i = 0; i < size; i++ )
        x += tags[i].getPositionX();

    x /= (double)size;

    return x;
}

double Cube::getPositionY()
{
    double y = 0.0;
    int size = tags.size();

    for( int i = 0; i < size; i++ )
        y += tags[i].getPositionY();

    y /= (double)size;

    return y;
}

double Cube::getPositionZ()
{
    double z = 0.0;
    int size = tags.size();

    for( int i = 0; i < size; i++ )
        z += tags[i].getPositionZ();

    z /= (double)size;

    return z;

}

double Cube::getDistance()
{
    return hypot( hypot( getPositionX(), getPositionY() ), getPositionZ() );
}

double Cube::getGroundDistance()
{
    return getDistance()*sin(1.13446);
}
