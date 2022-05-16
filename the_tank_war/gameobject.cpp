#include "gameobject.h"

int Gameobject::getPosition_y() const
{
    return position_y;
}

void Gameobject::setPosition_y(int value)
{
    position_y = value;
}

Gameobject::Direction Gameobject::getDirection() const
{
    return direction;
}

void Gameobject::setDirection(const Direction &value)
{
    direction = value;
}

int Gameobject::getWidth() const
{
    return width;
}

void Gameobject::setWidth(int value)
{
    width = value;
}

int Gameobject::getHeight() const
{
    return height;
}

void Gameobject::setHeight(int value)
{
    height = value;
}

Gameobject::Team Gameobject::getTeam() const
{
    return team;
}

void Gameobject::setTeam(const Team &value)
{
    team = value;
}

int Gameobject::getPosition_x() const
{
    return position_x;
}

void Gameobject::setPosition_x(int value)
{
    position_x = value;
}
