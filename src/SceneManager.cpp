#include "SceneManager.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

SceneManager::SceneManager(sf::RenderWindow *w) : m_window(w)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::handleEvents()
{
}

void SceneManager::handleInput()
{
}

void SceneManager::update(sf::Time dt)
{
}

void SceneManager::draw()
{
}

void SceneManager::setLevelFile(const std::string &fileName)
{
}