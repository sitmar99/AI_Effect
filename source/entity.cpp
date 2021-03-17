#include "entity.h"
#include <math.h>
#include <iostream>

float Entity::distanceTo(Entity* ent)
{
    sf::Vector2f here = this->getSprite()->getPosition();
    sf::Vector2f there = ent->getSprite()->getPosition();

    return sqrtf(powf(fabs(here.x - there.x), 2) + powf(fabs(here.y - there.y), 2));
}

bool Entity::update()
{
    if (hp <= 0)
        return false;


    iPos = sf::Vector2i(sprite.getPosition())/75;

    if (destination != sprite.getPosition())
    {
        sf::Vector2f unitDir(destination.x - sprite.getPosition().x,destination.y - sprite.getPosition().y);
        float distance = sqrtf(unitDir.x*unitDir.x+unitDir.y*unitDir.y);
        unitDir /= distance;

        if (distance < speed)
            sprite.setPosition(sf::Vector2f(destination));
        else
        {
            sf::Vector2f vel(unitDir * speed);
            sprite.move(vel);
        }
    }
    return true;
}

Entity::Entity(std::string pathToSprite, sf::Vector2f pos)
{     
    texture.loadFromFile(pathToSprite);
    sprite.setTexture(texture);

    sprite.setScale(sf::Vector2f(3,3));
    sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
    sprite.setPosition(pos);
    destination = pos;
}

Entity::Entity(std::string pathToSprite, sf::Vector2f pos, Entity* target): Entity(pathToSprite, pos)
{
    this->target = target;
}