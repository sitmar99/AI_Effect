#include "knight.h"

bool Knight::update()
{
    if (getSpecialAttacked() && time(NULL) - getTimeSpecialAttacked() >= getSpecialAttackDuration())
    {
        setDefence(getDefence() - 1);
        setDmg(getDmg() * 2);
        setSpecialAttacked(false);
    }
    return Entity::update();
}

void Knight::attack(Hero* target, std::vector<Projectile*> *projectiles)
{
    setTarget(target);
    if (distanceTo(target) <= getRange() && time(NULL) - getTimeAttacked() >= getRateOfAttack())
    {
        setDestination(getSprite()->getPosition());
        projectiles->push_back(new Swing(target->getSprite()->getPosition() - sf::Vector2f(10,10), target, getDmg()));
        setTimeAttacked(time(NULL));
    }
    else if (distanceTo(target) > getRange())
        setDestination(target->getSprite()->getPosition());
    else
        setDestination(getSprite()->getPosition());
}

void Knight::specialAttack(Hero* target)
{
    if (!target && time(NULL) - getTimeSpecialAttacked() >= getRateOfSpecialAttack())
    {
        setDefence(getDefence() + 1);
        setDmg(getDmg() / 2);
        setTimeSpecialAttacked(time(NULL));
        setSpecialAttacked(true);
    }
}

Knight::Knight(sf::Vector2f pos, int party): Hero("sprites/knight.png", pos, party)
{
    setType(1);
    setRange(10);
    setDmg(2);
    setHp(2);
    setRateOfAttack(2);
    setRateOfSpecialAttack(10);
    setSpecialAttackDuration(5);
}

Knight::Knight(std::string pathToSprite, sf::Vector2f pos, int party): Hero(pathToSprite, pos, party)
{
    setType(1);
    setRange(10);
    setDmg(2);
    setHp(2);
    setRateOfAttack(2);
    setRateOfSpecialAttack(10);
    setSpecialAttackDuration(5);
}