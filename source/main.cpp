#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <fstream>
#include <vector>
#include <math.h>
#include "entity.h"
#include "button.h"
#include "ai.h"
#include "hero.h"
#include "archer.h"
#include "mage.h"
#include "knight.h"

#define debug(x)  std::cerr << "(" << __LINE__ << ") " << #x << " == " << (x) << std::endl

int width = 600;
int height = 650;
int size = 8;

void selectAI(std::vector<Hero*>* heroes, Hero* hero)
{
    int iID = 0;
    int size = 16;
    float fSelectionScale = 1.2;

    sf::Font font;
    sf::Text text;
    if (!font.loadFromFile("fonts/Timeless.ttf"))
    {
        printf("Error while loading font!\n");
    }
    text.setFont(font);
    text.setFillColor(sf::Color::Black);

    std::vector<std::string> vecAiNames;
    std::fstream ais;
    std::string line;
    size_t pos;
    ais.open("source/ai.cpp");
    while (getline(ais, line))
    {
        pos = line.find("Name: ");
        if (pos != std::string::npos)
        {
            vecAiNames.push_back(line.substr(pos + 6));
        }
    }
    ais.close();

    sf::RectangleShape selection(sf::Vector2f(50, fSelectionScale * size));
    selection.setFillColor(sf::Color(128, 128, 128));
    sf::RectangleShape selected(sf::Vector2f(50, fSelectionScale * size));
    selected.setFillColor(sf::Color(128, 128, 128));

    sf::RenderWindow AiWindow(sf::VideoMode(75, 100), "select AI", sf::Style::None);
    AiWindow.setPosition(sf::Mouse::getPosition());
    
    while(AiWindow.isOpen())
    {
        iID = sf::Mouse::getPosition(AiWindow).y / size;

        text.setCharacterSize(size);
        selection.setSize(sf::Vector2f(75, fSelectionScale * size));
        selection.setPosition(sf::Vector2f(0, iID * size));
        selected.setSize(sf::Vector2f(75, fSelectionScale * size));
        selected.setPosition(sf::Vector2f(0, hero->getAiID() * size));

        sf::Event event;
        while(AiWindow.pollEvent(event))
        {
            if(!AiWindow.hasFocus())
                AiWindow.close();

            if(event.type == sf::Event::MouseWheelScrolled)
            {
                size += event.mouseWheelScroll.delta;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left)
            {
                hero->setAiID(iID);
                AiWindow.close();
                return;
            }
        }

        AiWindow.clear(sf::Color::White);
        AiWindow.draw(selection);
        AiWindow.draw(selected);
        
        for (int iter = 0; iter < vecAiNames.size(); iter++)
        {
            text.setString(vecAiNames[iter]);
            text.setPosition(0, size * iter);
            AiWindow.draw(text);
        }

        AiWindow.display();
    }
}

int heroesAliveInParty(std::vector<Hero*>* heroes, int party)
{
    int alive = 0;

    for (auto hero : (*heroes))
    {
        if (hero->getParty() == party)
            alive++;
    }
    return alive;
}

int buttonPressed(std::vector<Button*>* buttons, sf::Vector2f mousePos)
{
    for (auto button : (*buttons))
    {
        if(button->getSprite()->getGlobalBounds().contains(mousePos))
            return button->getID();

    }
    return 0;
}

int main()
    {
    //zmienne
    bool bPause = true;
    int iGameOver = 0;
    Hero* hDraged = nullptr;

    sf::Vector2f mysz;
    std::vector<Button*> buttons;
    std::vector<Hero*> heroes;
    std::vector<Hero*> heroesCopy;
    std::vector<Projectile*> projectiles;
    Ai artificial(&heroes, &projectiles);

    //Wczytywanie tła
    sf::Texture *tBackground = new sf::Texture;
    sf::Sprite *sBackground = new sf::Sprite;
    tBackground->loadFromFile("sprites/board.png");
    sBackground->setTexture(*tBackground);
    sBackground->setScale(sf::Vector2f(3,3));


    //generowanie okna
    sf::Event event;
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(width, height), "AI Effect", sf::Style::Default);
    window->setFramerateLimit(60);

    //dodanie guzikow
    buttons.push_back(new Button("sprites/reset.png", sf::Vector2f(2, 602), 0));
    buttons.push_back(new Button("sprites/play.png", sf::Vector2f(52, 602), 1));
    buttons.push_back(new Button("sprites/pause.png", sf::Vector2f(102, 602), 2));
    buttons.push_back(new Button("sprites/knight.png", sf::Vector2f(152, 602), 3));
    buttons.push_back(new Button("sprites/archer.png", sf::Vector2f(202, 602), 4));
    buttons.push_back(new Button("sprites/mage.png", sf::Vector2f(252, 602), 5));
    buttons.push_back(new Button("sprites/knight.png", sf::Vector2f(302, 602), 6));
    buttons.push_back(new Button("sprites/archer.png", sf::Vector2f(352, 602), 7));
    buttons.push_back(new Button("sprites/mage.png", sf::Vector2f(402, 602), 8));

    //glowna petla okna
    while(window->isOpen())
    {
        while(window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;

            case::sf::Event::MouseButtonPressed:
                switch (event.mouseButton.button)
                {
                case sf::Mouse::Button::Left:
                    switch (buttonPressed(&buttons, sf::Vector2f(sf::Mouse::getPosition(*window))))
                    {
                    case 0:
                        heroes = heroesCopy;
                        heroesCopy.clear();
                        for (auto proj : projectiles)
                            delete proj;
                        projectiles.clear();
                        bPause = true;
                        break;
                    case 1:
                        for (auto hero : heroes)
                        {
                            heroesCopy.push_back(hero->copy());
                        }
                        bPause = false;
                        break;
                    case 2:
                        bPause = true;
                        break;
                    case 3:
                        hDraged = new Knight(sf::Vector2f(sf::Mouse::getPosition(*window)), 0);
                        heroes.push_back(hDraged);
                        break;
                    case 4:
                        hDraged = new Archer(sf::Vector2f(sf::Mouse::getPosition(*window)), 0);
                        heroes.push_back(hDraged);
                        break;
                    case 5:
                        hDraged = new Mage(sf::Vector2f(sf::Mouse::getPosition(*window)), 0);
                        heroes.push_back(hDraged);
                        break;
                    case 6:
                        hDraged = new Knight(sf::Vector2f(sf::Mouse::getPosition(*window)), 1);
                        heroes.push_back(hDraged);
                        break;
                    case 7:
                        hDraged = new Archer(sf::Vector2f(sf::Mouse::getPosition(*window)), 1);
                        heroes.push_back(hDraged);
                        break;
                    case 8:
                        hDraged = new Mage(sf::Vector2f(sf::Mouse::getPosition(*window)), 1);
                        heroes.push_back(hDraged);
                        break;
                    default:
                        break;
                    }
                    break;
                case sf::Mouse::Button::Right:
                    for (auto hero : heroes)
                    {
                        if (hero->getSprite()->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window))))
                            selectAI(&heroes, hero);
                    }
                    break;
                default:
                    break;
                }
                break;

            case sf::Event::MouseMoved:
                if (hDraged != 0)
                {
                    hDraged->getSprite()->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
                } 
                break;

            case sf::Event::MouseButtonReleased:
                if (hDraged != 0)
                {
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*window));
                    pos.x = trunc((pos.x - 75) / 57) * 57 + 100.5;
                    pos.y = trunc((pos.y - 75) / 57) * 57 + 100.5;
                    hDraged->getSprite()->setPosition(pos);
                    hDraged = nullptr;
                }
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window->close();
                    break;
                case sf::Keyboard::Space:
                    bPause = !bPause;
                    break;
                case sf::Keyboard::A:   //hard coded move up
                    heroes[1]->setDestination(sf::Vector2f(heroes[1]->getSprite()->getPosition().x, heroes[1]->getSprite()->getPosition().y-58));
                    break;
                case sf::Keyboard::S:   //hard coded ai testing
                    artificial.play();
                    break;
                default:
                    break;
                }
                break;
            
            default:
                break;
            }
        }

        //clear window & draw background
        window->clear(sf::Color::Black);
        window->draw(*sBackground);
        

        if (!bPause)
        {
            if(!heroesAliveInParty(&heroes, 0))
            {
                iGameOver = 2;
                std::cout << "Winner is Player 2!\n";
                break;
            }
            if(!heroesAliveInParty(&heroes, 1))

            debug("flaming!");
            artificial.play();

            //check if hero dead
            for (auto iHero = heroes.begin(); iHero != heroes.end(); iHero++)
            {
                if (!(*iHero)->update())
                {
                    delete *iHero;
                    heroes.erase(iHero--);
                }
                else
                    window->draw(*(*iHero)->getSprite());
                
            }
            
            //draw projectiles & check if hit
            for (auto iPro=projectiles.begin(); iPro!=projectiles.end(); iPro++)
            {
                (*iPro)->update();
                if ((*iPro)->getSprite()->getPosition() == (*iPro)->getTarget()->getSprite()->getPosition())
                {
                    (*iPro)->getTarget()->decHpBy((*iPro)->getDmg());
                    delete *iPro;
                    projectiles.erase(iPro--);
                }
                else
                    window->draw(*(*iPro)->getSprite());
            }
        }

        if (bPause)
        {
            for (auto hero : heroes)
            {
                window->draw(*hero->getSprite());
            }
            for (auto proj : projectiles)
        {
            window->draw(*proj->getSprite());
        }
        }
        for (auto button : buttons)
        {
            window->draw(*button->getSprite());
        }

        window->display();
    }

    for (auto ent: heroes)
        delete ent;
    heroes.clear();
    for (auto ent: heroesCopy)
        delete ent;
    heroesCopy.clear();
    for (auto ent: projectiles)
        delete ent;
    projectiles.clear();

    return 0;
}

        //draw heroes (old)
        // for (auto ent : heroes)
        // {
        //     if (ent)
        //     {
        //         ent->update();
        //         window->draw(*ent->getSprite());
        //     }
        // }

        //draw grid
        // for (int x=1; x<size; x++)
        // {
        //     sf::RectangleShape line(sf::Vector2f(3,600));
        //     line.setPosition(int(x*600/size), 0);
        //     window->draw(line);
        // }
        // for (int y=1; y<size; y++)
        // {
        //     sf::RectangleShape line(sf::Vector2f(600, 3));
        //     line.setPosition(0, int(y*600/size));
        //     window->draw(line);
        // }
        
        //draw projectiles (old)
        // for (auto ent : projectiles)
        // {
        //     if (ent)
        //     {
        //         ent->update();
        //         window->draw(*ent->getSprite());
        //     }
        // }