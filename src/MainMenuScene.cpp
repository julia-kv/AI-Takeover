#include "MainMenuScene.h"
#include <iostream>

MainMenuScene::MainMenuScene(sf::RenderWindow *w) : m_window(w), m_background("MainMenuBackground.png")
{
    createButtons();
}

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::handleEvents(const sf::Event &event)
{
}

SceneType MainMenuScene::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
        for (Button &btn : m_buttons)
        {
            if (mousePos.x > btn.getPosition().x &&
                mousePos.x < btn.getPosition().x + btn.getSize().x &&
                mousePos.y > btn.getPosition().y &&
                mousePos.y < btn.getPosition().y + btn.getSize().y)
                return SceneType::GAMEPLAY;
        }
    }
    return SceneType::MAIN_MENU;
}

void MainMenuScene::update(sf::Time dt)
{
}

void MainMenuScene::draw() const
{
    m_window->draw(m_background);
    for (const Button &btn : m_buttons)
        m_window->draw(btn);
}

void MainMenuScene::createButtons()
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font from file arial.ttf" << std::endl;
    }

    m_buttons = {
        Button(m_window, {100.0, 40.0})};

    m_buttons[0].setPosition(sf::Vector2f(350.0, 285.0));
    m_buttons[0].setText("Play", m_font);
}

std::vector<Button> &MainMenuScene::getButtons()
{
    return m_buttons;
}