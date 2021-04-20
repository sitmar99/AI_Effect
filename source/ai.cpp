#include "ai.h"

void Ai::play()
{
    for(auto hero : (*heroes))
    {
        switch (hero->getAiID())
        {
        //Name: Archer sniper
        case 0:
            hero->specialAttack(nullptr);
            break;

        //Name: Archer dps
        case 1:
            hero->attack(hero->nearestEnemy(heroes), projectiles);
            break;
        
        //Name: Knight tank
        case 2:
            // hero->attack(hero->nearestEnemy(heroes), projectiles);
            hero->specialAttack(hero.get());
            hero->setDestination(hero->getFPos());
            break;

        //Name: Knight dps
        case 3:
            hero->attack(hero->nearestEnemy(heroes), projectiles);
            break;

        //Name: Mage
        case 4:
            if (hero->allyInRange(heroes))
                hero->specialAttack(hero->nearestAlly(heroes));
            // if (hero->enemyInRange(heroes))
            //     hero->attack(hero->nearestEnemy(heroes), projectiles);
            hero->setDestination(hero->getFPos());
            break;
        //Name: Dummy
        case 5:
            hero->setDestination(hero->getFPos());
            break;
        default:
            break;
        }
    }
}

Ai::Ai(std::vector<std::shared_ptr<Hero>> *heroesPtr, std::vector<std::shared_ptr<Projectile>> *projectilesPtr)
{
    heroes = heroesPtr;
    projectiles = projectilesPtr;
}