#include "ChooseLevelMenuScene.h"
#include <iostream>

ChooseLevelMenuScene::ChooseLevelMenuScene(sf::RenderWindow &w,
                                           SceneManager &sm) : m_window(w),
                                                               m_sceneManager(sm),
                                                               m_background("MainMenuBackground.png")
{
    createButtons();
}

ChooseLevelMenuScene::~ChooseLevelMenuScene()
{
}

void ChooseLevelMenuScene::handleEvents(const sf::Event &event)
{
}

SceneType ChooseLevelMenuScene::handleInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        for (int i = 0; i < m_buttons.size(); ++i)
            if (mousePos.x > m_buttons[i].getPosition().x &&
                mousePos.x < m_buttons[i].getPosition().x + m_buttons[i].getSize().x &&
                mousePos.y > m_buttons[i].getPosition().y &&
                mousePos.y < m_buttons[i].getPosition().y + m_buttons[i].getSize().y)
            {
                m_sceneManager.setLevel(i + 1);
                return SceneType::GAMEPLAY;
            }
    }
    return SceneType::CHOOSE_LEVEL_MENU;
}

SceneType ChooseLevelMenuScene::update(sf::Time dt)
{
    return SceneType::CHOOSE_LEVEL_MENU;
}

void ChooseLevelMenuScene::draw() const
{
    m_window.draw(m_background);
    for (const Button &btn : m_buttons)
        m_window.draw(btn);
}

void ChooseLevelMenuScene::createButtons()
{
    /* if (!m_font.loadFromFile("arial.ttf"))
    {
        std::cout << "Failed to load font from file 'arial.ttf'\n";
    }

    m_buttons = {
        Button({100.f, 40.f}),
        Button({100.f, 40.f})};

    m_buttons[0].setPosition(sf::Vector2f(350.0, 285.0));
    m_buttons[0].setText("Play", m_font); */
}