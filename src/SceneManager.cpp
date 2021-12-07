#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MainMenuScene.h"
#include "GameplayScene.h"
#include "ChooseLevelMenuScene.h"
#include "PauseScene.h"
#include <iostream>

SceneManager::SceneManager(sf::RenderWindow *w, const Constants &constants) : m_window(w),
                                                                              m_constants(constants),
                                                                              num_of_level(1)
{
    m_curScene = MAIN_MENU;
    m_scenes[MAIN_MENU] = std::make_unique<MainMenuScene>(w);
}

SceneManager::~SceneManager()
{
}

void SceneManager::handleEvents()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window->close();
            break;

        case sf::Event::KeyReleased:
            m_scenes[m_curScene]->handleEvents(event);
            break;

        case sf::Event::Resized:
        {
            sf::View view = m_window->getView();
            view.setSize(event.size.width, event.size.height);
            m_window->setView(view);
            break;
        }

        default:
            break;
        }
    }
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

void SceneManager::switchTo(SceneType newScene)
{
    switch (newScene)
    {
    case SceneType::MAIN_MENU:
        m_scenes[newScene] = std::make_unique<MainMenuScene>(m_window);
        break;

    case SceneType::CHOOSE_LEVEL_MENU:
        m_scenes[newScene] = std::make_unique<ChooseLevelMenuScene>(m_window, this);
        break;

    case SceneType::GAMEPLAY:
        m_scenes[newScene] = std::make_unique<GameplayScene>(m_window, num_of_level);
        break;

    case SceneType::PAUSE:
        m_scenes[newScene] = std::make_unique<PauseScene>(m_window);
        break;

    default:
        break;
    }

    if (m_curScene != SceneType::GAMEPLAY || newScene != SceneType::PAUSE)
        m_scenes[m_curScene].reset();

    m_curScene = newScene;
}