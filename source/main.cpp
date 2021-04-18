#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

#include <fstream>
#include <vector>
#include <math.h>
#include <memory>
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

void selectAI(std::vector<std::shared_ptr<Hero>>* heroes, Hero* hero)
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
void endScreen(sf::RenderWindow* window, int winner)
{
    sf::RenderWindow endScreen(sf::VideoMode(400,200), "endScreen", sf::Style::None);
    endScreen.setPosition(sf::Vector2i(window->getPosition() + sf::Vector2i(100,100)));
    
    while(endScreen.isOpen())
    {
        sf::Font font;
        sf::Text text;
        if (!font.loadFromFile("fonts/Timeless.ttf"))
            printf("Error while loading font!\n");
        text.setFont(font);
        text.setCharacterSize(48);
        text.setPosition(10,10);
        text.setFillColor(sf::Color::Black);
        text.setString("GAME OVER!\n Player " + std::to_string(winner) + " wins");
        sf::Event event;
        while(endScreen.pollEvent(event))
        {
            if(!endScreen.hasFocus())
                endScreen.close();
        }

        endScreen.clear(sf::Color::White);
        endScreen.draw(text);
        endScreen.display();
    }
}

int heroesAliveInParty(std::vector<std::shared_ptr<Hero>>* heroes, int party)
{
    int alive = 0;

    for (auto hero : (*heroes))
    {
        if (hero->getParty() == party)
            alive++;
    }
    return alive;
}

int buttonPressed(std::vector<std::shared_ptr<Button>>* buttons, sf::Vector2f mousePos)
{
    for (auto iButton : (*buttons))
    {
        if(iButton->getSprite()->getGlobalBounds().contains(mousePos))
            return iButton->getID();

    }
    return -1;
}
std::shared_ptr<Hero> heroPressed(std::vector<std::shared_ptr<Hero>>* heroes, sf::Vector2f mousePos)
{
    for(auto iHero : (*heroes))
    {
        if(iHero->getSprite()->getGlobalBounds().contains(mousePos))
            return iHero;
    }
    return nullptr;
}

int main()
    {
    bool bPause = true;
    int iGameOver = 0;
    std::shared_ptr<Hero> hDraged = nullptr;

    std::vector<std::shared_ptr<Button>> buttons;
    std::vector<std::shared_ptr<Hero>> heroes;
    std::vector<std::shared_ptr<Hero>> heroesCopy;
    std::vector<Projectile*> projectiles;
    Ai artificial(&heroes, &projectiles);

    sf::Texture *tBackground = new sf::Texture;
    sf::Sprite *sBackground = new sf::Sprite;
    tBackground->loadFromFile("sprites/board.png");
    sBackground->setTexture(*tBackground);
    sBackground->setScale(sf::Vector2f(3,3));

    sf::Event event;
    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(width, height), "AI Effect", sf::Style::Default);
    window->setFramerateLimit(60);

    buttons.push_back(std::make_shared<Button>("sprites/reset.png", sf::Vector2f(2, 602), 0));
    buttons.push_back(std::make_shared<Button>("sprites/play.png", sf::Vector2f(52, 602), 1));
    buttons.push_back(std::make_shared<Button>("sprites/pause.png", sf::Vector2f(102, 602), 2));
    buttons.push_back(std::make_shared<Button>("sprites/knight.png", sf::Vector2f(152, 602), 3));
    buttons.push_back(std::make_shared<Button>("sprites/archer.png", sf::Vector2f(202, 602), 4));
    buttons.push_back(std::make_shared<Button>("sprites/mage.png", sf::Vector2f(252, 602), 5));
    buttons.push_back(std::make_shared<Button>("sprites/knight.png", sf::Vector2f(302, 602), 6));
    buttons.push_back(std::make_shared<Button>("sprites/archer.png", sf::Vector2f(352, 602), 7));
    buttons.push_back(std::make_shared<Button>("sprites/mage.png", sf::Vector2f(402, 602), 8));
    buttons.push_back(std::make_shared<Button>("sprites/trash.png", sf::Vector2f(452, 602), 9));

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
                    hDraged = heroPressed(&heroes, sf::Vector2f(sf::Mouse::getPosition(*window)));

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
                        hDraged = std::make_shared<Knight>(sf::Vector2f(sf::Mouse::getPosition(*window)), 0);
                        heroes.push_back(hDraged);
                        break;
                    case 4:
                        hDraged =  std::make_shared<Archer>(sf::Vector2f(sf::Mouse::getPosition(*window)), 0);
                        heroes.push_back(hDraged);
                        break;
                    case 5:
                        hDraged = std::make_shared<Mage>(sf::Vector2f(sf::Mouse::getPosition(*window)), 0);
                        heroes.push_back(hDraged);
                        break;
                    case 6:
                        hDraged = std::make_shared<Knight>(sf::Vector2f(sf::Mouse::getPosition(*window)), 1);
                        heroes.push_back(hDraged);
                        break;
                    case 7:
                        hDraged = std::make_shared<Archer>(sf::Vector2f(sf::Mouse::getPosition(*window)), 1);
                        heroes.push_back(hDraged);
                        break;
                    case 8:
                        hDraged = std::make_shared<Mage>(sf::Vector2f(sf::Mouse::getPosition(*window)), 1);
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
                            selectAI(&heroes, hero.get());
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
                    if (buttons.back()->getSprite()->getGlobalBounds().contains(pos))
                    {
                        for (auto iHero = heroes.begin(); iHero != heroes.end(); iHero++)
                        {
                            if (*iHero == hDraged)
                            {
                                heroes.erase(iHero--);
                                break;
                            }
                        }
                    }
                    else
                    {
                        pos.x = trunc((pos.x - 75) / 57) * 57 + 100.5;
                        pos.y = trunc((pos.y - 75) / 57) * 57 + 100.5;
                        hDraged->getSprite()->setPosition(pos);
                    }
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
                default:
                    break;
                }
                break;
            
            default:
                break;
            }
        }

        window->clear(sf::Color::Black);
        window->draw(*sBackground);

        if(!bPause && !heroesAliveInParty(&heroes, 0))
        {
            bPause = true;
            endScreen(window, 2);
        }
        if(!bPause && !heroesAliveInParty(&heroes, 1))
        {
            bPause = true;
            endScreen(window, 1);
        }

        if (!bPause)
        {
            artificial.play();

            if(heroes.size())
                for (auto iHero = heroes.begin(); iHero != heroes.end(); iHero++)
                {
                    if (!(*iHero)->update())
                    {
                        heroes.erase(iHero--);
                    }
                    else
                        window->draw(*(*iHero)->getSprite());
                    
                }
            
            if(projectiles.size())
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
            if (heroes.size())
                for (auto hero : heroes)
                {
                    window->draw(*hero->getSprite());
                }
            if (projectiles.size())
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

    heroes.clear();
    heroesCopy.clear();
    for (auto ent: projectiles)
        delete ent;
    projectiles.clear();

    return 0;
}