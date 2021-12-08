#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "Background.h"
#include "Gui.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene(sf::RenderWindow &);
    ~MainMenuScene();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    SceneType update(sf::Time);
    void draw() const;

private:
    void createButtons();

    sf::RenderWindow &m_window;
    Gui m_gui;
    sf::Font m_font;
    Background m_background;
};