#ifndef ARCHER_H
#define ARCHER_H

#include "hero.h"
#include "arrow.h"

class Archer: public Hero
{
private:

public:
    bool update();
    void attack(Hero* target, std::vector<Projectile*> *projectiles);
    void specialAttack(Hero* target);
    std::shared_ptr<Hero> copy();

    Archer(sf::Vector2f pos, int party);
    Archer(sf::Vector2f pos, int party, int AiID);
    Archer(std::string pathToSprite, sf::Vector2f pos, int party);
    ~Archer() {};
};

#endif