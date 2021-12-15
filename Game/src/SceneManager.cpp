#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "MainMenuScene.h"
#include "GameplayScene.h"
#include "ChooseLevelMenuScene.h"
#include "PauseScene.h"
#include <iostream>

SceneManager::SceneManager(sf::RenderWindow &w,
                           const Constants &constants) : m_window(w),
                                                         m_constants(constants),
                                                         m_curScene(SceneType::MAIN_MENU),
                                                         m_sceneToSwitch(SceneType::MAIN_MENU),
                                                         m_numOfLevel(1)
{
    m_scenes[SceneType::MAIN_MENU] = std::make_unique<MainMenuScene>(m_window, *this);
}

SceneManager::~SceneManager()
{
}

bool SceneManager::cycle(sf::Time dt)
{
    handleEvents();
    m_scenes[m_curScene]->handleInput();
    m_scenes[m_curScene]->update(dt);
    if (m_curScene != m_sceneToSwitch)
        changeScene();
    return false;
}

void SceneManager::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;

        case sf::Event::Resized:
        {
            sf::View view = m_window.getView();
            view.setSize(event.size.width, event.size.height);
            m_window.setView(view);
            break;
        }

        case sf::Event::KeyReleased:
            m_scenes[m_curScene]->handleEvents(event);
            break;

        default:
            break;
        }
    }
}

void SceneManager::draw() const
{
    m_scenes[m_curScene]->draw();
}

void SceneManager::switchTo(const SceneType scn)
{
    m_sceneToSwitch = scn;
}

void SceneManager::changeScene()
{
    switch (m_sceneToSwitch)
    {
    case SceneType::MAIN_MENU:
        m_scenes[m_sceneToSwitch] = std::make_unique<MainMenuScene>(m_window, *this);
        break;

    case SceneType::CHOOSE_LEVEL_MENU:
        m_scenes[m_sceneToSwitch] = std::make_unique<ChooseLevelMenuScene>(m_window, *this);
        break;

    case SceneType::GAMEPLAY:
        if (m_curScene != SceneType::PAUSE)
            m_scenes[m_sceneToSwitch] = std::make_unique<GameplayScene>(m_window, m_numOfLevel, m_constants, *this);
        break;

    case SceneType::PAUSE:
        m_scenes[m_sceneToSwitch] = std::make_unique<PauseScene>(m_window, *this);
        break;

    default:
        break;
    }

    if (m_curScene != SceneType::GAMEPLAY || m_sceneToSwitch != SceneType::PAUSE)
        m_scenes[m_curScene].reset(nullptr);

    m_curScene = m_sceneToSwitch;
}

void SceneManager::setLevel(const size_t lvl)
{
    m_numOfLevel = lvl;
}