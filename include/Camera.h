#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Camera
{

public:
    Camera(sf::RenderWindow &w, Hero &h, const float tile_size) : m_window(w),
                                                                  m_hero(h),
                                                                  m_tileSize(tile_size)
    {
    }

    ~Camera()
    {
    }

    void update()
    {
        sf::View view = m_window.getView();
        float x_pos = m_hero.getPosition().x + m_tileSize / 2;
        float del_x = x_pos - view.getCenter().x;
        float halfTileSize = (float)m_window.getSize().x / 2;
        float padding = 0.2 * halfTileSize;
        if (std::abs(del_x) <= padding)
            return;

        x_pos += del_x < 0 ? padding : -padding;
        x_pos = std::max(x_pos, halfTileSize);
        x_pos = std::min(x_pos, max_size - halfTileSize);

        view.setCenter(x_pos, (float)m_window.getSize().y / 2);
        m_window.setView(view);
    }

    void setMaxSize(float ms)
    {
        max_size = ms;
    }

private:

    const float m_tileSize;
    sf::RenderWindow &m_window;
    Hero &m_hero;
    float max_size;
};