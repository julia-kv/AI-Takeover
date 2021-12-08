#include "Level.h"
#include <string>
#include <fstream>
#include <iostream>

Level::Level(sf::RenderWindow &w,
             const size_t num_of_level,
             Constants &constants) : m_window(w),
                                     m_constants(constants),
                                     m_camera(w, m_hero),
                                     m_background("Background_" + std::to_string(num_of_level) + ".png")

{
    readLevelFile(num_of_level);
}

Level::~Level()
{
}

void Level::handleEvents(const sf::Event &event)
{
    switch (event.type)
    {
    case sf::Event::KeyReleased:
        if (event.key.code == sf::Keyboard::Left ||
            event.key.code == sf::Keyboard::Right ||
            event.key.code == sf::Keyboard::Up ||
            event.key.code == sf::Keyboard::Down)
            m_hero.keyReleased(event.key.code);
        break;

    default:
        break;
    }
}

SceneType Level::handleInput()
{
    m_hero.handleInput();
    return SceneType::GAMEPLAY;
}

SceneType Level::update(sf::Time dt)
{
    m_map.update(dt);
    m_hero.update(dt);
    check_hero_state();
    m_background.update(m_window.getView());
    m_camera.update();
    return SceneType::GAMEPLAY;
}

void Level::check_hero_state()
{
    if (m_hero.isFinished())
    {
        /// m_finish.changeTexture();
    }
    else if (m_hero.isDead())
    {
        ///
    }
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_background);
    target.draw(m_map);
    target.draw(m_finish);
    target.draw(m_hero);
}

void Level::readLevelFile(const size_t num_of_level)
{
    m_map.setSize(m_constants.at("TILE_SIZE"));
    m_map.setVelocity(m_constants.at("PLATFORM_VELOCITY"));
    m_map.readMap(num_of_level);

    m_hero.setMap(&m_map);
    m_hero.setSize(m_constants.at("TILE_SIZE"));
    m_hero.setVelocity(m_constants.at("HERO_VELOCITY"));
    m_hero.setAcceleration(m_constants.at("HERO_ACCELERATION"));
    m_hero.setInitialPosition(m_map.getHeroPosition());

    m_finish.setSize(m_constants.at("TILE_SIZE"));
    m_finish.setPosition(m_map.getFinishPosition());

    m_camera.setMaxSize(m_map.getSize().x * m_constants.at("TILE_SIZE"));
}

Map &Level::getMap()
{
    return m_map;
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