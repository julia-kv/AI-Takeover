#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Camera
{
    float tile_size = 40.0f;

public:
    Camera(sf::RenderWindow *w, Hero *h, Map *m) : m_window(w),
                                                   m_hero(h),
                                                   m_map(m)
    {
    }

    ~Camera()
    {
    }

    void update()
    {
        sf::View view = m_window->getView();
        float x_pos = m_hero->getPosition().x + tile_size / 2;
        x_pos = std::max(x_pos, (float)m_window->getSize().x / 2);
        x_pos = std::min(x_pos, (float)m_map->getSize().x * tile_size - (float)m_window->getSize().x / 2);
        view.setCenter(x_pos, m_window->getSize().y / 2); // ???
        m_window->setView(view);

        /* std::cout << "Hero position : " << m_window->mapCoordsToPixel(m_hero->getPosition()).x
                  << ", " << m_window->mapCoordsToPixel(m_hero->getPosition()).y << '\n';

        std::cout << "Window size: " << m_window->getSize().x << " , " << m_window->getSize().y << '\n'; */
    }

private:
    sf::RenderWindow *m_window;
    Hero *m_hero;
    Map *m_map;
};