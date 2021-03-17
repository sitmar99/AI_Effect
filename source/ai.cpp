#include "ai.h"

void Ai::play()
{
    for(auto ent : entities)
    {
        if (ent->nearestEnemy(heroes))
            ent->setDestination(ent->nearestEnemy(heroes)->getSprite()->getPosition()); 
    }
}

void Ai::add(Hero *ent)
{
    entities.push_back(ent);
}

Ai::Ai(std::vector<Hero*> *heroesPtr, std::vector<Projectile*> *projectilesPtr)
{
    heroes = heroesPtr;
    projectiles = projectilesPtr;
}