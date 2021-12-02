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
        switch(ch)
        {
            case '*':
                color = sf::Color(163, 163, 194);
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

        std::cout << "m_vertices size: " << m_vertices.size() << '\n';
    }

    void draw()
    {
        m_window->draw(m_vertices.data(), m_vertices.size(), sf::Quads);
    }

    sf::Vector2i getSize()
    {
        return m_map_size;
    }

    std::vector<sf::Vertex>& getVertexArray()
    {
        return m_vertices;
    }

private:
    sf::Vector2i m_map_size;
    std::vector<sf::Vertex> m_vertices;
    sf::RenderWindow *m_window;
};