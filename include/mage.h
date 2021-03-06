#ifndef MAGE_H
#define MAGE_H

#include "hero.h"
#include "fireball.h"

class Mage: public Hero
{
private:

public:
    bool update();
    void attack(Hero* target, std::vector<std::shared_ptr<Projectile>> *projectiles);
    void specialAttack(Hero* target);
    std::shared_ptr<Hero> copy();

    Mage(sf::Vector2f pos, int party);
    Mage(sf::Vector2f pos, int party, int AiID);
    Mage(std::string pathToSprite, sf::Vector2f pos, int party);
    ~Mage() {};
};

#endif