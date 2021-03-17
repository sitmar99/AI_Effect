#ifndef AI_H
#define AI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "hero.h"
#include "projectile.h"
#include <vector>

class Ai
{
private:
    std::vector<Hero*> *heroes;
    std::vector<Projectile*> *projectiles;
    std::vector<Hero*> entities;

public:
    std::vector<Hero*> getEntities() { return this->entities; };
    void addHero(Hero* ent) { this->entities.push_back(ent); };

    void play();
    void add(Hero *ent);

    Ai(std::vector<Hero*> *heroesPtr, std::vector<Projectile*> *projectilesPtr);
    ~Ai() {};
};

#endif