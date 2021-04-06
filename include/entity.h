#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <string>
#include <iostream>

class Entity
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    int dmg;
    int hp = 1;

    sf::Vector2f destination;
    Entity* target;
    float speed = 2.f;

public:
    sf::Texture *getTexture() {return &texture; }
    sf::Sprite *getSprite() { return &sprite; }
    
    int getDmg() { return dmg; }
    void setDmg(int newDmg) { dmg = newDmg; }
    int getHp() { return hp; }
    void setHp(int newHp) { hp = newHp; }
    void decHp() { hp--; }
    void incHp() { hp++; }
    void decHpBy(int iSub) { hp -= iSub; }

    sf::Vector2f getFPos() { return sprite.getPosition(); }
    void setDestination(sf::Vector2f newDest) { destination = newDest; }
    sf::Vector2f getDestination() { return destination; }
    void setTarget(Entity *newTarget) { target = newTarget; }
    Entity* getTarget() { return target; }

    float distanceTo(Entity *ent);
    bool update();

    Entity() {};
    Entity(std::string pathToSprite, sf::Vector2f pos);
    Entity(std::string pathToSprite, sf::Vector2f pos, Entity* target);
    ~Entity() {};
};

#endif