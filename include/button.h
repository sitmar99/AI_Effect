#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Button
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    int ID;

public:
    sf::Texture *getTexture() {return &texture; }
    sf::Sprite *getSprite() { return &sprite; }
    int getID() { return ID; }

    Button() {};
    Button(std::string pathToSprite, sf::Vector2f pos);
    ~Button();
};

#endif