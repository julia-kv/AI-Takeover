#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Level.h"

class Hero
{
    float tile_size = 40.0f;

public:
    Hero()
    {
        m_rect.setFillColor(sf::Color::Cyan);
        m_rect.setOutlineThickness(-1);
        m_rect.setOutlineColor(sf::Color::Black);
        m_hero_vel = 300.0f;
        m_acceleration = 1000.0;
        is_flying = true;
    }
    ~Hero(){};

    sf::Vector2f getPosition()
    {
        return m_rect.getPosition();
    }

    void setSize(float size)
    {
        m_rect.setSize(sf::Vector2f(size, size * 2));
    }

    void setInitialPosition(int tile_x, int tile_y)
    {
        m_rect.setPosition((tile_x - 1) * m_rect.getSize().x,
                           (tile_y - 1) * m_rect.getSize().x);
    }

    void update(sf::Time dt)
    {
        if (is_flying)
            m_vel.y += m_acceleration * dt.asSeconds();
        sf::Vector2f del = m_vel * dt.asSeconds();
        move(del);
    }

    void handleEvents()
    {
    }

    void key_released(sf::Keyboard::Key code)
    {
        if (code == sf::Keyboard::Left || code == sf::Keyboard::Right)
            m_vel.x = 0;
    }

    void handleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_vel.x = -m_hero_vel;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_vel.x = m_hero_vel;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !is_flying)
        {
            m_vel.y = -1.5*m_hero_vel;
            is_flying = true;
        }
    }

    void draw()
    {
        m_window->draw(m_rect);
    }

    void setWindow(sf::RenderWindow *w)
    {
        m_window = w;
    }

    void setMap(Map *map)
    {
        m_map = map;
    }

    bool isFinished()
    {
        return false;
    }

    bool isDead()
    {
        return false;
    }

private:
    void move(sf::Vector2f del)
    {
        if (del.x > 0)
            del.x = std::min(del.x, tile_size / 2);
        else
            del.x = std::max(del.x, -tile_size / 2);

        if (del.y > 0)
            del.y = std::min(del.y, tile_size / 2);
        else
            del.y = std::max(del.y, -tile_size / 2);

        move_x(del.x);
        move_y(del.y);
    }

    void move_x(float dx)
    {
        if (dx == 0)
            return;

        m_rect.move(dx, 0);
        float rect_left = m_rect.getPosition().x;
        float rect_right = m_rect.getPosition().x + m_rect.getSize().x;
        float rect_top = m_rect.getPosition().y;
        float rect_bottom = m_rect.getPosition().y + m_rect.getSize().y;

        std::vector<sf::Vertex> vertices = m_map->getVertexArray();

        for (int i = 0; i < vertices.size(); i += 4)
        {
            float tile_left = vertices[i].position.x;
            float tile_right = vertices[i + 2].position.x;
            float tile_top = vertices[i].position.y;
            float tile_bottom = vertices[i + 2].position.y;

            // возможно здесь проверка на движение игрока вместе с платформой
            /* if (tile_top == rect_bottom)
            {

            } */

            if ((rect_top < tile_bottom && tile_bottom < rect_bottom) ||
                (rect_top < tile_top && tile_top < rect_bottom) ||
                (rect_top == tile_top && rect_bottom == tile_bottom))
            {
                if (dx > 0)
                {
                    if (rect_left < tile_left && tile_left < rect_right)
                        m_rect.setPosition(tile_left - tile_size, rect_top);
                        
                }
                else
                {
                    if (rect_left < tile_right && tile_right < rect_right)
                        m_rect.setPosition(tile_right, rect_top);
                }
            }
        }
    }

    void move_y(float dy)
    {
        if (dy == 0)
            return;

        is_flying = true;
        m_rect.move(0, dy);

        float rect_left = m_rect.getPosition().x;
        float rect_right = m_rect.getPosition().x + m_rect.getSize().x;
        float rect_top = m_rect.getPosition().y;
        float rect_bottom = m_rect.getPosition().y + m_rect.getSize().y;

        std::vector<sf::Vertex> vertices = m_map->getVertexArray();
        for (int i = 0; i < vertices.size(); i += 4)
        {
            float tile_left = vertices[i].position.x;
            float tile_right = vertices[i + 2].position.x;
            float tile_top = vertices[i].position.y;
            float tile_bottom = vertices[i + 2].position.y;

            if ((rect_left < tile_right && tile_right < rect_right) ||
                (rect_left < tile_left && tile_left < rect_right) ||
                (rect_left == tile_left && rect_right && tile_right))
            {
                if (dy > 0)
                {
                    if (rect_top < tile_top && tile_top < rect_bottom)
                    {
                        m_rect.setPosition(rect_left, tile_top - 2 * tile_size);
                        is_flying = false;
                    }
                }
                else
                {
                    if (rect_top < tile_bottom && tile_bottom < rect_bottom)
                    {
                        m_rect.setPosition(rect_left, tile_bottom);
                        m_vel.y = 0;
                    }
                }
            }
        }
    }

    sf::Vector2f m_vel;
    sf::RectangleShape m_rect;
    sf::RenderWindow *m_window;
    float m_hero_vel, m_acceleration;
    Map *m_map;
    bool is_flying;
};