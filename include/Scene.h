#pragma once
#include "SFML/System.hpp"
#include "SceneType.h"

class Scene
{
public:
    Scene(){};
    ~Scene(){};

    virtual void handleEvents() = 0;
    virtual SceneType handleInput() = 0;
    virtual void update(sf::Time) = 0;
    virtual void draw() = 0;
};