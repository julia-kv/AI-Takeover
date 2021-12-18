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
                                                         m_curScene(SceneType::PAUSE),
                                                         m_sceneToSwitch(SceneType::MAIN_MENU),
                                                         m_numOfLevel(1),
                                                         m_initializationSuccess(true)
{
    try
    {
        changeScene();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
        m_initializationSuccess = false;
    }
}

SceneManager::~SceneManager()
{
}

bool SceneManager::cycle(sf::Time dt)
{
    // returns true if error happens
    // returns false if success
    handleEvents();
    m_scenes[m_curScene]->handleInput();
    m_scenes[m_curScene]->update(dt);
    if (m_curScene != m_sceneToSwitch)
    {
        try
        {
            changeScene();
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
            return true;
        }
    }
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

        default:
            m_scenes[m_curScene]->handleEvents(event);
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

bool SceneManager::successfullyInitialized() const
{
    return m_initializationSuccess;
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