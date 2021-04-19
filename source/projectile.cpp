#include "projectile.h"

void Projectile::update()
{
    setDestination(getTarget()->getSprite()->getPosition());

    Entity::update();
    
    sf::Sprite* sprite = getSprite();
    float rot = atan2((getDestination().y-sprite->getPosition().y),(getDestination().x-sprite->getPosition().x));
    rot *= (180.0/M_PI);
    rot += 90;

    sprite->setRotation(rot);
}

Projectile::Projectile(std::string pathToSprite, sf::Vector2f pos): Entity(pathToSprite, pos) { setSpeed(4.f); }
Projectile::Projectile(std::string pathToSprite, sf::Vector2f pos, Entity* target): Entity(pathToSprite, pos, target) { setSpeed(4.f); }
