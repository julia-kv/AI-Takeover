#include "Level.h"
#include <string>
#include <fstream>
#include <iostream>

Level::Level(sf::RenderWindow *w, const std::string &fn) : m_window(w),
                                                           m_camera(w, &m_hero, &m_map)
{
    std::cout << "Level ctor(sf::RenderWindow *w, const std::string &fn)\n";
    readLevelFile(fn);
}

Level::~Level()
{
    std::cout << "Level dtor\n";
    m_platforms.clear();
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
            m_hero.key_released(event.key.code);
        break;

    case sf::Event::Resized:
    {
        m_camera.event_resized(event);
        break;
    }

    default:
        break;
    }
}

SceneType Level::handleInput()
{
    m_hero.handleInput();
    return SceneType::GAMEPLAY;
}

void Level::update(sf::Time dt)
{
    m_hero.update(dt);
    check_hero_state();
    m_background.update(m_window->getView());
    m_camera.update();
}

void Level::check_hero_state()
{
    if (m_hero.isFinished())
    {
        ///
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
    target.draw(m_hero);
}

void Level::readLevelFile(const std::string &fn)
{
    std::string line;
    std::ifstream myfile(fn);
    if (!myfile.is_open())
    {
        std::cout << "Failed to open level file \'" << fn << '\'' << std::endl;
        return;
    }

    int num_tiles_x = 0, num_tiles_y = 0;
    myfile >> num_tiles_x >> num_tiles_y;
    getline(myfile, line);

    m_map = Map(num_tiles_x, num_tiles_y);
    for (int i = 0; i < num_tiles_y; ++i)
    {
        getline(myfile, line);
        for (int j = 0; j < num_tiles_x; ++j)
            if (line[j] != ' ')
                m_map.addTile(i, j, line[j]);
    }

    int hero_init_pos_x = 0, hero_init_pos_y = 0;
    myfile >> hero_init_pos_x >> hero_init_pos_y;
    //m_hero.setSize(40.0f);
    m_hero.setInitialPosition(hero_init_pos_x, hero_init_pos_y);
    m_hero.setMap(&m_map);

    myfile.close();
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