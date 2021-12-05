#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneType.h"

class Scene
{
public:
    Scene(){};
    virtual ~Scene(){};

    virtual void handleEvents(const sf::Event &event) = 0;
    virtual SceneType handleInput() = 0;
    virtual void update(sf::Time) = 0;
    virtual void draw() = 0;
};