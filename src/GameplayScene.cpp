#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow *w, const size_t num_of_level) : m_window(w),
                                                                               m_level(w, num_of_level)
{
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::handleEvents(const sf::Event &event)
{
    m_level.handleEvents(event);
}

SceneType GameplayScene::handleInput()
{
    return m_level.handleInput();
}

void GameplayScene::update(sf::Time dt)
{
    m_level.update(dt);
}

void GameplayScene::draw() const
{
    m_window->draw(m_level);
}