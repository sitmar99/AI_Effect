#ifndef FIREBALL_H
#define FIREBALL_H

#include "projectile.h"

class Fireball: public Projectile
{
private:

public:
    Fireball(sf::Vector2f pos, Entity* target, int dmg);
    ~Fireball() {};
};

#endif