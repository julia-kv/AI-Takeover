#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Camera
{
public:
    Camera(){};
    ~Camera(){};
    sf::Vector2f getCenter()
    {
        return m_center;
    }

private:
    sf::Vector2f m_center;
};