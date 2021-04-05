#include "ai.h"

void Ai::play()
{
    for(auto ent : entities)
    {
        switch (ent->getAiID())
        {
        //Name: example
        case 1:
            if (ent->nearestEnemy(heroes))
                ent->setDestination(ent->nearestEnemy(heroes)->getSprite()->getPosition()); 
            if (ent->enemyInRange(heroes))
                ent->attack(ent->enemyWithLowestHP(heroes), projectiles);
            break;
        
        //Name: Lorem
        case 2:
            break;

        //Name: Ipsum
        case 3:
            break;
        default:
            break;
        }
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