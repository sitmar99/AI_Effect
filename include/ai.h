#ifndef AI_H
#define AI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "hero.h"
#include "projectile.h"
#include <vector>
#include <memory>

class Ai
{
private:
    std::vector<std::shared_ptr<Hero>> *heroes;
    std::vector<Projectile*> *projectiles;

public:
    void play();

    Ai(std::vector<std::shared_ptr<Hero>> *heroesPtr, std::vector<Projectile*> *projectilesPtr);
    ~Ai() {};
};

#endif