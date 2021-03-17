#include "fireball.h"

Fireball::Fireball(sf::Vector2f pos, Entity* target, int dmg): Projectile("sprites/fireball.png", pos, target)
{
    setDmg(dmg);
}