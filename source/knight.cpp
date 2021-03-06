#include "knight.h"

bool Knight::update()
{
    if(getSpecialAttacked())
    {
        getSprite()->setTextureRect(sf::IntRect(16, 0, 32, 16));
    }
    if (getSpecialAttacked() && time(NULL) - getTimeSpecialAttacked() >= getSpecialAttackDuration())
    {
        setDefence(getDefence() - 1);
        setDmg(getDmg() * 2);
        setSpecialAttacked(false);
        getSprite()->setTextureRect(sf::IntRect(0,0,16,16));
    }

    return Entity::update();
}

void Knight::attack(Hero* target, std::vector<std::shared_ptr<Projectile>> *projectiles)
{
    setTarget(target);
    if (distanceTo(target) <= getRange() && time(NULL) - getTimeAttacked() >= getRateOfAttack())
    {
        setDestination(getSprite()->getPosition());
        projectiles->push_back(std::make_shared<Swing>(target->getSprite()->getPosition() - sf::Vector2f(10,10), target, getDmg()));
        setTimeAttacked(time(NULL));
    }
    else if (distanceTo(target) > getRange())
        setDestination(target->getSprite()->getPosition());
    else
        setDestination(getSprite()->getPosition());
}

void Knight::specialAttack(Hero* target)
{
    if ((!target || target == this) && time(NULL) - getTimeSpecialAttacked() >= getRateOfSpecialAttack())
    {
        setDefence(getDefence() + 1);
        setDmg(getDmg() / 2);
        setTimeSpecialAttacked(time(NULL));
        setSpecialAttacked(true);
    }
}
std::shared_ptr<Hero> Knight::copy()
{
    return std::make_shared<Knight>(getFPos(), getParty(), getAiID());
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
Knight::Knight(sf::Vector2f pos, int party, int AiID): Hero("sprites/knight.png", pos, party, AiID)
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