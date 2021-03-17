#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
#include <math.h>

class Projectile: public Entity
{
private:

public:
    void update();

    Projectile(std::string pathToSprite, sf::Vector2f pos);
    Projectile(std::string pathToSprite, sf::Vector2f pos, Entity* target);
    ~Projectile() {};
};

#endif