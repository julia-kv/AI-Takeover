#include "PauseScene.h"
#include <iostream>

PauseScene::PauseScene(sf::RenderWindow &w,
                       SceneSwitcher &scn_switcher) : m_window(w),
                                                      m_background("../Files/PauseBackground.png"),
                                                      m_gui(w),
                                                      m_sceneSwitcher(scn_switcher)
{
    m_gui.addButton("Continue");
    m_gui.addButton("Exit");
}

PauseScene::~PauseScene()
{
}

void PauseScene::handleEvents(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            switch (m_gui.getPressedButton())
            {
            case 0:
                m_sceneSwitcher.switchTo(SceneType::GAMEPLAY);
                break;

            case 1:
            {
                m_window.close();
                break;
            }

            default:
                break;
            }
        }
    }
}

void PauseScene::handleInput()
{
}

void PauseScene::update(sf::Time dt)
{
}

void PauseScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}