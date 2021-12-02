#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Level.h"

class Hero
{
public:
    Hero()
    {
        m_rect.setFillColor(sf::Color::Cyan);
        m_rect.setOutlineThickness(-1);
        m_rect.setOutlineColor(sf::Color::Black);
        m_hero_vel = 300.0f;
        m_acceleration = 0.0;
    }
    ~Hero(){};

    sf::Vector2f getPosition()
    {
        return m_position;
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
        m_vel.y += m_acceleration * dt.asSeconds();
        sf::Vector2f del = m_vel * dt.asSeconds();
        move(del);
    }

    void handleEvents()
    {
    }

    void key_released(sf::Keyboard::Key code)
    {
        if (code == sf::Keyboard::Left ||
            code == sf::Keyboard::Right)
            m_vel.x = 0;
        else if (code == sf::Keyboard::Up ||
                 code == sf::Keyboard::Down)
            m_vel.y = 0;
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            m_vel.y = -m_hero_vel;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            m_vel.y = m_hero_vel;
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

private:
    void move(sf::Vector2f del)
    {
        m_rect.move(del);
        sf::Rect<float> r(m_rect.getPosition(), m_rect.getSize());

        std::vector<sf::Vertex> vertices = m_map->getVertexArray();
        bool flag = true;
        for (int i = 0; i < vertices.size() && flag; i += 4)
        {
            if (del.x > 0 && (r.contains(vertices[i].position) || r.contains(vertices[i + 3].position)))
            {
                del.x = vertices[i].position.x - (m_rect.getPosition().x + m_rect.getSize().x);
                flag = false;
            }
            if (del.x < 0 && (r.contains(vertices[i + 1].position) || r.contains(vertices[i + 2].position)))
            {
                del.x = vertices[i + 2].position.x - m_rect.getPosition().x;
                flag = false;
            }
        }

        flag = true;
        for (int i = 0; i < vertices.size() && flag; i += 4)
        {
            if (del.y > 0 && (r.contains(vertices[i].position) || r.contains(vertices[i + 1].position)))
            {
                del.y = vertices[i].position.y - (m_rect.getPosition().y + m_rect.getSize().y);
                flag = false;
            }
            if (del.y < 0 && (r.contains(vertices[i + 2].position) || r.contains(vertices[i + 3].position)))
            {
                del.y = vertices[i + 2].position.y - m_rect.getPosition().y;
                flag = false;
            }
        }
        m_rect.move(del);
    }

    sf::Vector2f m_position;
    sf::Vector2f m_vel;
    sf::RectangleShape m_rect;
    sf::RenderWindow *m_window;
    float m_hero_vel, m_acceleration;
    Map *m_map;
};