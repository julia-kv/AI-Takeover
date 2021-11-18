#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Hero
{
public:
    Hero(){};
    ~Hero(){};
    sf::Vector2f getPosition()
    {
        return m_position;
    }
private:
    sf::Vector2f m_position;
};