#include "Level.h"

Level::Level(sf::RenderWindow *w, const std::string &fn) : m_window(w)
{
    readLevelFile(fn);
}

Level::~Level() {}

void Level::handleEvents() {}

SceneType Level::handleInput()
{
    return SceneType::GAMEPLAY;
}

void Level::update(sf::Time dt) {}

void Level::draw() {}

void Level::readLevelFile(const std::string &fn)
{
}

Map &Level::getMap()
{
    return m_map;
}

std::vector<Platform> &Level::getPlatforms()
{
    return m_platforms;
}

Hero &Level::getHero()
{
    return m_hero;
}

Finish &Level::getFinish()
{
    return m_finish;
}

Camera &Level::getCamera()
{
    return m_camera;
}