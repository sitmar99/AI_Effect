#include "mage.h"

bool Mage::update()
{
    return Entity::update();
}

void Mage::attack(Hero* target, std::vector<Projectile*> *projectiles)
{
    setTarget(target);
    if (distanceTo(target) <= getRange() && time(NULL) - getTimeAttacked() >= getRateOfAttack())
    {
        setDestination(getSprite()->getPosition());
        projectiles->push_back(new Fireball(getSprite()->getPosition(), target, getDmg()));
        setTimeAttacked(time(NULL));
    }
    else if (distanceTo(target) > getRange())
        setDestination(target->getSprite()->getPosition());
    else
        setDestination(getSprite()->getPosition());
}

void Mage::specialAttack(Hero* target )
{
    if (target && time(NULL) - getTimeSpecialAttacked() >= getRateOfSpecialAttack())
    {
        target->incHp();
        decHp();
        setTimeSpecialAttacked(time(NULL));
    }
}

Mage::Mage(sf::Vector2f pos, int party): Hero("sprites/mage.png", pos, party)
{
    setType(2);
    setRange(12);
    setDmg(2);
    setHp(2);
    setRateOfAttack(3);
    setRateOfSpecialAttack(10);
}

Mage::Mage(std::string pathToSprite, sf::Vector2f pos, int party): Hero(pathToSprite, pos, party)
{
    setType(2);
    setRange(12);
    setDmg(2);
    setHp(2);
    setRateOfAttack(3);
    setRateOfSpecialAttack(10);
}