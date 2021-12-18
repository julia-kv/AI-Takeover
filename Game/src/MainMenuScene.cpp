#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(sf::RenderWindow &w,
                             SceneSwitcher &scn_switcher) : m_window(w),
                                                            m_background("../Files/MainMenuBackground.png"),
                                                            m_gui(w),
                                                            m_sceneSwitcher(scn_switcher)
{
    sf::View view = m_window.getView();
    view.setCenter(m_window.getSize().x / 2, m_window.getSize().y / 2);
    m_window.setView(view);
    m_gui.addButton("Play");
    m_gui.addButton("Exit");
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::handleEvents(const sf::Event &event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            switch (m_gui.getPressedButton())
            {
            case 0:
                m_sceneSwitcher.switchTo(SceneType::CHOOSE_LEVEL_MENU);
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

void MainMenuScene::handleInput()
{
}

void MainMenuScene::update(sf::Time dt)
{
}

void MainMenuScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}