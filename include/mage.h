#ifndef MAGE_H
#define MAGE_H

#include "hero.h"
#include "fireball.h"

class Mage: public Hero
{
private:

public:
    bool update();
    void attack(Hero* target, std::vector<Projectile*> *projectiles);
    void specialAttack(Hero* target);
    Hero* copy();

    Mage(sf::Vector2f pos, int party);
    Mage(std::string pathToSprite, sf::Vector2f pos, int party);
    ~Mage() {};
};

#endif