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

public:
    void play();

    Ai(std::vector<Hero*> *heroesPtr, std::vector<Projectile*> *projectilesPtr);
    ~Ai() {};
};

#endif