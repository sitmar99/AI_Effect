#include "swing.h"

Swing::Swing(sf::Vector2f pos, Entity* target, int dmg): Projectile("sprites/sword_swing.png", pos, target)
{
    setDmg(dmg);
}
