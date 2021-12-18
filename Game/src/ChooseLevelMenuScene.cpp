#include "ChooseLevelMenuScene.h"
#include <iostream>

ChooseLevelMenuScene::ChooseLevelMenuScene(sf::RenderWindow &w,
                                           SceneManager &sm) : m_window(w),
                                                               m_sceneManager(sm),
                                                               m_background("../Files/MainMenuBackground.png"),
                                                               m_gui(w)
{
    m_gui.addButton("Level 1");
    m_gui.addButton("Level 2");
}

ChooseLevelMenuScene::~ChooseLevelMenuScene()
{
}

void ChooseLevelMenuScene::handleEvents(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            switch (m_gui.getPressedButton())
            {
            case 0:
            {
                m_sceneManager.setLevel(1);
                m_sceneManager.switchTo(SceneType::GAMEPLAY);
                break;
            }

            case 1:
            {
                m_sceneManager.setLevel(2);
                m_sceneManager.switchTo(SceneType::GAMEPLAY);
                break;
            }

            default:
                break;
            }
        }
    }
}

void ChooseLevelMenuScene::handleInput()
{
}

void ChooseLevelMenuScene::update(sf::Time dt)
{
}

void ChooseLevelMenuScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}