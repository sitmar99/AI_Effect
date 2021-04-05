#include "ai.h"

void Ai::play()
{
    for(auto ent : entities)
    {
        switch (ent->getAiID())
        {
        //Name: Archer sniper
        case 0:
            if (!ent->enemyInRange(heroes))
                ent->specialAttack(nullptr);
            ent->attack(ent->enemyWithLowestHP(heroes), projectiles);
            break;

        //Name: Archer dps
        case 1:
            ent->attack(ent->nearestEnemy(heroes), projectiles);
            break;
        
        //Name: Knight tank
        case 2:
            ent->specialAttack(ent);
            ent->attack(ent->nearestEnemy(heroes), projectiles);
            break;

        //Name: Knight dps
        case 3:
            ent->attack(ent->nearestEnemy(heroes), projectiles);
            break;

        //Name: Mage
        case 4:
            if (ent->allyInRange(heroes))
                ent->specialAttack(ent->allyWithLowestHP(heroes));
            if (ent->enemyInRange(heroes))
                ent->attack(ent->nearestEnemy(heroes), projectiles);
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