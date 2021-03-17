#include "hero.h"

Hero* Hero::nearestAlly(std::vector<Hero*> *heroes)
{
    float minDistance = 600;
    Hero* closestAlly = nullptr;

    for (auto iHero : (*heroes))
    {
        if (iHero != this)
        {
            if (party == iHero->getParty() && iHero->distanceTo(this) < minDistance)
            {
                minDistance = iHero -> distanceTo(this);
                closestAlly = iHero;
            }        
        }
    }

    return closestAlly ? closestAlly : this;
}

Hero* Hero::nearestEnemy(std::vector<Hero*> *heroes)
{
    float minDistance = 600;
    Hero* closestEnemy = nullptr;

    for (auto iHero : (*heroes))
    {
        if (iHero != this)
        {
            if (party != iHero->getParty() && iHero->distanceTo(this) < minDistance)
            {
                minDistance = iHero -> distanceTo(this);
                closestEnemy = iHero;
            }        
        }
    }

    return closestEnemy;
}

Hero* Hero::allyWithLowestHP(std::vector<Hero*> *heroes)
{
    int lowestHP = getHp();
    Hero* lowestAlly = this;

    for (auto iHero : (*heroes))
    {
        if (party == iHero->getParty() && iHero->getHp() < lowestHP)
        {
            lowestHP = iHero->getHp();
            lowestAlly = iHero;
        }
    }

    return lowestAlly;
}

Hero* Hero::enemyWithLowestHP(std::vector<Hero*> *heroes)
{
    int lowestHP = 10;
    Hero* lowestEnemy = nullptr;

    for (auto iHero : (*heroes))
    {
        if (party == iHero->getParty() && iHero->getHp() < lowestHP)
        {
            lowestHP = iHero->getHp();
            lowestEnemy = iHero;
        }
    }

    return lowestEnemy;
}

bool Hero::allyInRange(std::vector<Hero*> *heroes)
{
    for (auto iHero : (*heroes))
    {
        if (party == iHero->getParty() && distanceTo(iHero) <= getRange())
            return true;
    }
    return false;
}

bool Hero::enemyInRange(std::vector<Hero*> *heroes)
{
    for (auto iHero : (*heroes))
    {
        if (party != iHero->getParty() && distanceTo(iHero) <= getRange())
            return true;
    }
    return false;
}

Hero::Hero(std::string pathToSprite, sf::Vector2f pos, int party): Entity(pathToSprite, pos)
{
    this->party = party;
    timeAttacked = 0;
    timeSpecialAttacked = 0;
    specialAttacked = false;
}