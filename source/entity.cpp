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

    if (destination != sprite.getPosition())
    {
        sf::Vector2f vecDirection(destination.x - sprite.getPosition().x,destination.y - sprite.getPosition().y);
        float distance = sqrtf(vecDirection.x*vecDirection.x+vecDirection.y*vecDirection.y);
        vecDirection /= distance;

        if (distance < speed)
            sprite.setPosition(sf::Vector2f(destination));
        else
        {
            sf::Vector2f vel(vecDirection * speed);
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
    sprite.setOrigin(texture.getSize().x/2.0,texture.getSize().y/2.0);
    sprite.setPosition(pos);
    destination = pos;
}

Entity::Entity(std::string pathToSprite, sf::Vector2f pos, Entity* target): Entity(pathToSprite, pos)
{
    this->target = target;
}