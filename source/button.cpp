#include "button.h"

Button::Button(std::string pathToSprite, sf::Vector2f pos, int ID)
{
    texture.loadFromFile(pathToSprite);
    sprite.setTexture(texture);

    sprite.setScale(sf::Vector2f(3,3));

    sprite.setPosition(pos);

    this->ID = ID;
}