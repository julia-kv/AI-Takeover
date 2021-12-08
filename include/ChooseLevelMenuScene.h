#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "Background.h"
#include "Gui.h"

class ChooseLevelMenuScene : public Scene
{
public:
    ChooseLevelMenuScene(sf::RenderWindow &, SceneManager &);
    ~ChooseLevelMenuScene();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    SceneType update(sf::Time);
    void draw() const;

private:
    void createButtons();

    Gui m_gui;
    sf::RenderWindow &m_window;
    SceneManager &m_sceneManager;
    sf::Font m_font;
    Background m_background;
};