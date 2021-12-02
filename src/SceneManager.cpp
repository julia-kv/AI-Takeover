#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MainMenuScene.h"
#include "GameplayScene.h"
#include <iostream>

SceneManager::SceneManager(sf::RenderWindow *w) : m_window(w)
{
    std::cout << "SceneManager ctor(sf::RenderWindow *w)\n";
    m_curScene = MAIN_MENU;
    m_scenes[MAIN_MENU] = std::make_unique<MainMenuScene>(w);

    m_levelFile = "Level_1.txt";
}

SceneManager::~SceneManager()
{
    std::cout << "SceneManager dtor\n";
}

void SceneManager::handleEvents(const sf::Event& event)
{
    m_scenes[m_curScene]->handleEvents(event);
}

void SceneManager::handleInput()
{
    SceneType scn = m_scenes[m_curScene]->handleInput();
    if (scn != m_curScene)
        switchTo(scn);
}

void SceneManager::update(sf::Time dt)
{
    m_scenes[m_curScene]->update(dt);
}

void SceneManager::draw()
{
    m_scenes[m_curScene]->draw();
}

void SceneManager::setLevelFile(const std::string &fileName)
{
}

void SceneManager::switchTo(SceneType scene_to_switch)
{
    if (m_curScene == SceneType::MAIN_MENU &&
        scene_to_switch == SceneType::GAMEPLAY)
    {
        std::cout << "SceneManager: switching from MAIN_MENU to GAMEPLAY\n";
        m_scenes[SceneType::GAMEPLAY] = std::make_unique<GameplayScene>(m_window, m_levelFile);
        m_scenes[m_curScene].reset();
        std::cout << "Deleted MainMenu ptr\n";
        m_curScene = SceneType::GAMEPLAY;
    }
}