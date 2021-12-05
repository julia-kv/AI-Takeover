#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Button.h"
#include "SceneType.h"
#include <vector>

class PauseScene : public Scene
{
public:
    PauseScene(sf::RenderWindow *);
    ~PauseScene();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    void update(sf::Time);
    std::vector<Button> &getButtons();
    void draw();

private:
    void createButtons();

    sf::RenderWindow *m_window;
    std::vector<Button> m_buttons;
};