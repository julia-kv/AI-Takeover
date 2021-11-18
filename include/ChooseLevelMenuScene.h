#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

class ChooseLevelMenuScene : public Scene
{
public:
    ChooseLevelMenuScene(sf::RenderWindow *, SceneManager *);
    ~ChooseLevelMenuScene();

    void handleEvents();
    SceneType handleInput();
    void update(sf::Time);
    void draw();

    std::vector<Button>& getButtons();

private:
    void createButtons();

    std::vector<Button> m_buttons;
    sf::RenderWindow *m_window;
    SceneManager *m_sceneManager;
};