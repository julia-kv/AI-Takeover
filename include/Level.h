#pragma once
#include "SceneType.h"
#include "Platform.h"
#include "Map.h"
#include "Hero.h"
#include "Finish.h"
#include "Camera.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <string>
#include "Background.h"
#include "Constants.h"

class Level : public sf::Drawable, public sf::Transformable
{
public:
    Level(sf::RenderWindow &, const size_t, Constants &constants);
    ~Level();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    SceneType update(sf::Time);

    Map &getMap();
    std::vector<Platform> &getPlatforms();
    Hero &getHero();
    Finish &getFinish();
    Camera &getCamera();

private:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
    void readLevelFile(const std::string &);
    void check_hero_state();

    sf::RenderWindow &m_window;
    Map m_map;
    std::vector<Platform> m_platforms;
    Hero m_hero;
    Finish m_finish;
    Camera m_camera;
    Background m_background;
    Constants &m_constants;
};