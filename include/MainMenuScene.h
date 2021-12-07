#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

class MainMenuScene : public Scene
{
public:
    MainMenuScene(sf::RenderWindow *);
    ~MainMenuScene();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    void update(sf::Time);
    void draw() const;
    std::vector<Button> &getButtons();

private:
    void createButtons();

    sf::RenderWindow *m_window;
    std::vector<Button> m_buttons;
    sf::Font m_font;
};