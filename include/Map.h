#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

class Map
{
    float tile_size = 40.0f;

public:
    Map()
    {
    }

    Map(int num_tiles_x, int num_tiles_y, sf::RenderWindow *w) : m_map_size(num_tiles_x, num_tiles_y),
                                                                 m_window(w)
    {
    }

    ~Map(){};

    void addTile(int i, int j, char ch)
    {

        sf::Vector2f pos0(j * tile_size, i * tile_size);
        sf::Vector2f pos1((j + 1) * tile_size, i * tile_size);
        sf::Vector2f pos2((j + 1) * tile_size, (i + 1) * tile_size);
        sf::Vector2f pos3(j * tile_size, (i + 1) * tile_size);

        sf::Vertex vert0(pos0);
        sf::Vertex vert1(pos1);
        sf::Vertex vert2(pos2);
        sf::Vertex vert3(pos3);

        sf::Color color(sf::Color::White);
        switch (ch)
        {
        case '*':
            color = sf::Color::Red;
            break;

        case '-':
            color = sf::Color::Yellow;
            break;

        default:
            break;
        }

        vert0.color = color;
        vert1.color = color;
        vert2.color = color;
        vert3.color = color;

        m_vertices.push_back(vert0);
        m_vertices.push_back(vert1);
        m_vertices.push_back(vert2);
        m_vertices.push_back(vert3);
    }

    void addPlatform(float x1, float x2, float y)
    {
    }

    void update()
    {
        /* for (int i = index; i < vertices.size(); i += 4)
        {
            vertices[i].position.x += del_x;
            vertices[i].position.y += del_y;
        } */
    }

    void draw()
    {
        m_window->draw(m_vertices.data(), m_vertices.size(), sf::Quads);
    }

    sf::Vector2i getSize()
    {
        return m_map_size;
    }

    std::vector<sf::Vertex> &getVertexArray()
    {
        return m_vertices;
    }

private:
    sf::Vector2i m_map_size;
    std::vector<sf::Vertex> m_vertices;
    sf::RenderWindow *m_window;
};

/* class Platforms
{
public:

    void func()
    {
        for (int i = 0; i < borders.size(); ++i)
        {
            int j = 4 * i;
            j
        }
    }

    void update()
    {
        for (int i = index; i < vertices.size(); i += 4)
        {
            vertices[i].position.x += del_x;
            vertices[i].position.y += del_y;
        }
    }


    void addPlatform(float x1, float x2, float y)
    {
        vertices.push_back(sf::Vertex(sf::Vector2f(x1, y)));
        vertices.push_back(sf::Vertex(sf::Vector2f(x1 + tile_size, y)));
        vertices.push_back(sf::Vertex(sf::Vector2f(x1 + tile_size, y + tile_size)));
        vertices.push_back(sf::Vertex(sf::Vector2f(x1, y + tile_size)));

        borders.push_back(std::make_pair(x1, x2));
    }

private:
    std::vector<sf::Vertex> vertices;
    std::vector<std::pair<float,float>> borders;
    int index;
}; */