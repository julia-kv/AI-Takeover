#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "Background.h"
#include "Gui.h"
#include "SceneSwitcher.h"

class MainMenuScene : public Scene
{
public:
    MainMenuScene(sf::RenderWindow &, SceneSwitcher &);
    ~MainMenuScene();
    MainMenuScene(const MainMenuScene &) = delete;
    MainMenuScene(MainMenuScene &&) noexcept = delete;
    MainMenuScene &operator=(const MainMenuScene &) = delete;
    MainMenuScene &operator=(MainMenuScene &&) noexcept = delete;

    void handleEvents(const sf::Event &event);
    void handleInput();
    void update(sf::Time);
    void draw() const;

private:
    sf::RenderWindow &m_window;
    Background m_background;
    Gui m_gui;
    SceneSwitcher &m_sceneSwitcher;
};