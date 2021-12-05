#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

class Map : public sf::Drawable, public sf::Transformable
{
    float tile_size = 40.0f;

public:
    Map()
    {
    }

    Map(int num_tiles_x, int num_tiles_y) : m_map_size(num_tiles_x, num_tiles_y)
    {
        if (!m_texture.loadFromFile("texture.png"))
        {
            std::cout << "Failed to load texture.png file\n";
        }
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

        /* vert0.color = color;
        vert1.color = color;
        vert2.color = color;
        vert3.color = color; */

        vert0.texCoords = sf::Vector2f(0.f, 0.f);
        vert1.texCoords = sf::Vector2f(64.f, 0.f);
        vert2.texCoords = sf::Vector2f(64.f, 64.f);
        vert3.texCoords = sf::Vector2f(0.f, 64.f);

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

            vertices[i + 1].position.x += del_x;
            vertices[i + 1].position.y += del_y;

            vertices[i + 2].position.x += del_x;
            vertices[i + 2].position.y += del_y;

            vertices[i + 3].position.x += del_x;
            vertices[i + 3].position.y += del_y;

        } */
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
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &m_texture;
        target.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);
    }

    sf::Vector2i m_map_size;
    std::vector<sf::Vertex> m_vertices;
    sf::Texture m_texture;
};