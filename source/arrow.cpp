#include "arrow.h"

Arrow::Arrow(sf::Vector2f pos, Entity* target, int dmg): Projectile("sprites/arrow.png", pos, target)
{
    setDmg(dmg);
}
