#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(sf::RenderWindow &w) : m_window(w),
                                                    m_background("MainMenuBackground.png"),
                                                    m_gui(w)
{
    m_gui.addButton("Play");
    m_gui.addButton("Exit");
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::handleEvents(const sf::Event &event)
{
    if (event.type == sf::Event::Resized)
    {
        //m_gui.updatePositions();
    }
}

SceneType MainMenuScene::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        switch (m_gui.getPressedButton())
        {
        case 0:
            return SceneType::GAMEPLAY;
            break;

        case 1:
            return SceneType::GAMEPLAY;
            break;

        default:
            break;
        }
    }
    return SceneType::MAIN_MENU;
}

SceneType MainMenuScene::update(sf::Time dt)
{
    return SceneType::MAIN_MENU;
}

void MainMenuScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_gui);
}

void MainMenuScene::createButtons()
{
    /* if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font from file 'arial.ttf'\n";
    }

    m_buttons = {Button({100.0, 40.0})};

    m_buttons[0].setPosition(sf::Vector2f(350.0, 285.0));
    m_buttons[0].setText("Play", m_font); */
}