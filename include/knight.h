#ifndef KNIGHT_H
#define KNIGHT_H

#include "hero.h"
#include "swing.h"

class Knight: public Hero
{
private:

public:
    bool update();
    void attack(Hero* target, std::vector<Projectile*> *projectiles);
    void specialAttack(Hero* target);
    Hero* copy();

    Knight(sf::Vector2f pos, int party);
    Knight(sf::Vector2f pos, int party, int AiID);
    Knight(std::string pathToSprite, sf::Vector2f pos, int party);
    ~Knight() {};
};

#endif