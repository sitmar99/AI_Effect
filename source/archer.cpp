#include "archer.h"
#include <iostream>

bool Archer::update()
{
    if(getSpecialAttacked())
    {
        getSprite()->setTextureRect(sf::IntRect(16,0,32,16));
    }
    if (getSpecialAttacked() && time(NULL) - getTimeSpecialAttacked() >= getSpecialAttackDuration())
    {
        setRange(getRange() / 2);
        setRateOfAttack(getRateOfAttack() / 2);
        setSpecialAttacked(false);
        getSprite()->setTextureRect(sf::IntRect(0,0,16,16));
    }
    return Entity::update();
}

void Archer::attack(Hero* target, std::vector<std::shared_ptr<Projectile>> *projectiles)
{
    setTarget(target);
    if (distanceTo(target) <= getRange() && time(NULL) - getTimeAttacked() >= getRateOfAttack())
    {
        setDestination(getSprite()->getPosition());
        projectiles->push_back(std::make_shared<Arrow>(getSprite()->getPosition(), target, getDmg()));
        setTimeAttacked(time(NULL));
    }
    else if (distanceTo(target) > getRange())
        setDestination(target->getSprite()->getPosition());
    else
        setDestination(getSprite()->getPosition());
}

void Archer::specialAttack(Hero* target)
{
    if (!target && time(NULL) - getTimeSpecialAttacked() >= getRateOfSpecialAttack())
    {
        setRange(getRange() * 2);
        setRateOfAttack(getRateOfAttack() * 2);
        setTimeSpecialAttacked(time(NULL));
        setSpecialAttacked(true);
    }
}

std::shared_ptr<Hero> Archer::copy()
{
    return std::make_shared<Archer>(getFPos(), getParty(), getAiID());
}

Archer::Archer(sf::Vector2f pos, int party): Hero("sprites/archer.png", pos, party)
{
    setType(0);
    setRange(200);
    setDmg(2);
    setHp(1);
    setRateOfAttack(3);
    setRateOfSpecialAttack(10);
    setSpecialAttackDuration(5);
}
Archer::Archer(sf::Vector2f pos, int party, int AiID): Hero("sprites/archer.png", pos, party, AiID)
{
    setType(0);
    setRange(200);
    setDmg(2);
    setHp(1);
    setRateOfAttack(3);
    setRateOfSpecialAttack(10);
    setSpecialAttackDuration(5);
}
Archer::Archer(std::string pathToSprite, sf::Vector2f pos, int party): Hero(pathToSprite, pos, party)
{
    setType(0);
    setRange(300);
    setDmg(2);
    setHp(1);
    setRateOfAttack(3);
    setRateOfSpecialAttack(10);
    setSpecialAttackDuration(5);
}