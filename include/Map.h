#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Map
{
public:
    Map(){};
    ~Map(){};
    sf::Vector2i getSize()
    {
        return m_size;
    }

private:
    sf::Vector2i m_size;
};