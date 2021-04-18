#include "hero.h"

Hero* Hero::nearestAlly(std::vector<std::shared_ptr<Hero>> *heroes)
{
    float minDistance = 600;
    std::shared_ptr<Hero> closestAlly = nullptr;

    for (auto iHero : (*heroes))
    {
        if (iHero.get() != this)
        {
            if (party == iHero->getParty() && iHero->distanceTo(this) < minDistance)
            {
                minDistance = iHero -> distanceTo(this);
                closestAlly = iHero;
            }        
        }
    }

    return closestAlly ? closestAlly.get() : this;
}

Hero* Hero::nearestEnemy(std::vector<std::shared_ptr<Hero>> *heroes)
{
    float minDistance = 600;
    std::shared_ptr<Hero> closestEnemy = nullptr;

    for (auto iHero : (*heroes))
    {
        if (iHero.get() != this)
        {
            if (party != iHero->getParty() && iHero->distanceTo(this) < minDistance)
            {
                minDistance = iHero -> distanceTo(this);
                closestEnemy = iHero;
            }        
        }
    }

    return closestEnemy.get();
}

Hero* Hero::allyWithLowestHP(std::vector<std::shared_ptr<Hero>> *heroes)
{
    int lowestHP = getHp();
    std::shared_ptr<Hero> lowestAlly;

    for (auto iHero : (*heroes))
    {
        if (party == iHero->getParty() && iHero->getHp() < lowestHP)
        {
            lowestHP = iHero->getHp();
            lowestAlly = iHero;
        }
    }

    return lowestAlly ? lowestAlly.get() : this;
}

Hero* Hero::enemyWithLowestHP(std::vector<std::shared_ptr<Hero>> *heroes)
{
    int lowestHP = 100;
    std::shared_ptr<Hero> lowestEnemy = nullptr;

    for (auto iHero : (*heroes))
    {
        if (party != iHero->getParty() && iHero->getHp() < lowestHP)
        {
            lowestHP = iHero->getHp();
            lowestEnemy = iHero;
        }
    }

    return lowestEnemy.get();
}

bool Hero::allyInRange(std::vector<std::shared_ptr<Hero>> *heroes)
{
    for (auto iHero : (*heroes))
    {
        if (party == iHero->getParty() && distanceTo(iHero) <= getRange())
            return true;
    }
    return false;
}

bool Hero::enemyInRange(std::vector<std::shared_ptr<Hero>> *heroes)
{
    for (auto iHero : (*heroes))
    {
        if (party != iHero->getParty() && distanceTo(iHero) <= getRange())
            return true;
    }
    return false;
}

Hero::Hero(std::string pathToSprite, sf::Vector2f pos, int party, int AiID): Entity(pathToSprite, pos)
{
    this->party = party;
    timeAttacked = 0;
    timeSpecialAttacked = 0;
    specialAttacked = false;
    this->aiID = AiID;
}


Hero::Hero(std::string pathToSprite, sf::Vector2f pos, int party): Entity(pathToSprite, pos)
{
    this->party = party;
    timeAttacked = 0;
    timeSpecialAttacked = 0;
    specialAttacked = false;
    aiID = 0;
}