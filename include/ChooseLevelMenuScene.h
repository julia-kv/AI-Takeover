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
    ChooseLevelMenuScene(sf::RenderWindow &, SceneManager *);
    ~ChooseLevelMenuScene();

    void handleEvents(const sf::Event& event);
    SceneType handleInput();
    SceneType update(sf::Time);
    void draw() const;

    std::vector<Button>& getButtons();

private:
    void createButtons();

    std::vector<Button> m_buttons;
    sf::RenderWindow &m_window;
    SceneManager *m_sceneManager;
};