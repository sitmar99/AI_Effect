#ifndef ARROW_H
#define ARROW_H

#include "projectile.h"

class Arrow: public Projectile
{
private:

public:
    Arrow(sf::Vector2f pos, Entity* target, int dmg);
    ~Arrow() {};
};

#endif