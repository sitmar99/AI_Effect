#ifndef SWING_H
#define SWING_H

#include "projectile.h"

class Swing: public Projectile
{
private:

public:
    Swing(sf::Vector2f pos, Entity* target, int dmg);
    ~Swing() {};
};

#endif