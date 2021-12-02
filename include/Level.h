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

class Level
{
public:
    Level(sf::RenderWindow *, const std::string &);
    ~Level();

    void handleEvents(const sf::Event& event);
    SceneType handleInput();
    void update(sf::Time);
    void draw();

    Map &getMap();
    std::vector<Platform> &getPlatforms();
    Hero &getHero();
    Finish &getFinish();
    Camera &getCamera();

private:
    void readLevelFile(const std::string &);

    sf::RenderWindow *m_window;
    Map m_map;
    std::vector<Platform> m_platforms;
    Hero m_hero;
    Finish m_finish;
    Camera m_camera;
};