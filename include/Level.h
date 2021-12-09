#pragma once
#include "SceneType.h"
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
    Level(sf::RenderWindow &, const size_t, Constants &);
    ~Level();

    void handleEvents(const sf::Event &event);
    SceneType handleInput();
    SceneType update(sf::Time);

    Map &getMap();
    Hero &getHero();
    Finish &getFinish();

private:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
    void readLevelFile(const size_t);
    SceneType checkHeroState();

    sf::RenderWindow &m_window;
    Map m_map;
    Hero m_hero;
    Finish m_finish;
    Camera<Hero> m_camera;
    Constants &m_constants;
};