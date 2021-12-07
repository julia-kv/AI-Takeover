#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

typedef sf::Vector2<float> vector2f;

class Map : public sf::Drawable, public sf::Transformable
{

    float tile_size = 40.0f;
    float platform_vel = 80.0f;

public:
    Map() {}

    Map(int num_tiles_x, int num_tiles_y) : m_map_size(num_tiles_x, num_tiles_y),
                                            m_right_border(false),
                                            m_platform_count(0)
    {
        if (!m_texture.loadFromFile("texture.png"))
        {
            std::cout << "Failed to load texture.png file\n";
        }
    }

    ~Map(){};

    void addTile(int i, int j, char ch)
    {
        switch (ch)
        {

        case '*':
        {
            addTileStatic(i, j);
            break;
        }

        case '-':
        {
            addPlatform(i, j);
            break;
        }

        case '!':
        {
            vector2f finish_pos(j * tile_size, i * tile_size);
            m_finish_pos = finish_pos;
            break;
        }

        case 'h':
        {
            vector2f hero_pos(j * tile_size, i * tile_size);
            m_hero_pos = hero_pos;
            break;
        }

        default:
            break;
        }
    }

    void addTileStatic(int i, int j)
    {

        sf::Vector2f pos0(j * tile_size, i * tile_size);
        sf::Vector2f pos1((j + 1) * tile_size, i * tile_size);
        sf::Vector2f pos2((j + 1) * tile_size, (i + 1) * tile_size);
        sf::Vector2f pos3(j * tile_size, (i + 1) * tile_size);

        sf::Vertex vert0(pos0);
        sf::Vertex vert1(pos1);
        sf::Vertex vert2(pos2);
        sf::Vertex vert3(pos3);

        vert0.texCoords = sf::Vector2f(0, 0);
        vert1.texCoords = sf::Vector2f(64, 0);
        vert2.texCoords = sf::Vector2f(64, 64);
        vert3.texCoords = sf::Vector2f(0, 64);

        /* sf::Color color(sf::Color::White);
        color = sf::Color::Red;

        vert0.color = color;
        vert1.color = color;
        vert2.color = color;
        vert3.color = color; */

        m_vertices.push_back(vert0);
        m_vertices.push_back(vert1);
        m_vertices.push_back(vert2);
        m_vertices.push_back(vert3);

        ++m_platform_count;
    }

    void addPlatform(int i, int j)
    {
        if (!m_right_border)
        {

            sf::Vector2f pos0(j * tile_size, i * tile_size);
            sf::Vector2f pos1((j + 1) * tile_size, i * tile_size);
            sf::Vector2f pos2((j + 1) * tile_size, (i + 1) * tile_size);
            sf::Vector2f pos3(j * tile_size, (i + 1) * tile_size);

            sf::Vertex vert0(pos0);
            sf::Vertex vert1(pos1);
            sf::Vertex vert2(pos2);
            sf::Vertex vert3(pos3);

            vert0.texCoords = sf::Vector2f(64, 0);
            vert1.texCoords = sf::Vector2f(128, 0);
            vert2.texCoords = sf::Vector2f(128, 64);
            vert3.texCoords = sf::Vector2f(64, 64);

            /* sf::Color color(sf::Color::White);
            color = sf::Color::Yellow;

            vert0.color = color;
            vert1.color = color;
            vert2.color = color;
            vert3.color = color; */

            m_vertices.push_back(vert0);
            m_vertices.push_back(vert1);
            m_vertices.push_back(vert2);
            m_vertices.push_back(vert3);

            m_platform_idx.push_back(m_platform_count);
            ++m_platform_count;
            m_right_border = true;
        }
        else
        {

            auto platform_borders = std::make_pair(m_vertices[(m_platform_count - 1) * 4].position.x, (float)(j + 1) * tile_size);
            m_borders.push_back(platform_borders);
            m_platform_vel.push_back(platform_vel);
            m_right_border = false;
        }
    }

    void update(sf::Time dt)
    {
        size_t j = 0;

        for (auto it : m_platform_idx)
        {

            if (m_vertices[it * 4].position.x <= m_borders[j].first)
            {
                m_platform_vel[j] = platform_vel;
            }

            if (m_vertices[it * 4 + 2].position.x >= m_borders[j].second)
            {
                m_platform_vel[j] = -1 * platform_vel;
            }

            vector2f del(m_platform_vel[j] * dt.asSeconds(), 0);

            m_vertices[it * 4].position += del;
            m_vertices[it * 4 + 1].position += del;
            m_vertices[it * 4 + 2].position += del;
            m_vertices[it * 4 + 3].position += del;

            ++j;
        }
    }

    sf::Vector2i getSize()
    {
        return m_map_size;
    }

    std::vector<sf::Vertex> &getVertexArray()
    {
        return m_vertices;
    }

    bool isPlatformMoving(int platform_idx)
    {
        for (size_t i = 0; i < m_platform_idx.size(); ++i)
        {

            if (m_platform_idx[i] == platform_idx)
                return true;
        }
        return false;
    }

    vector2f getPlatformPosition(int platform_idx)
    {
        return vector2f(m_vertices[platform_idx * 4].position.x,
                        m_vertices[platform_idx * 4].position.y - tile_size);
    }

    float getPlatformVel(int platform_idx)
    {
        int j = 0;
        bool is_find = false;
        for (size_t i = 0; i < m_platform_idx.size(); ++i)
        {
            if (m_platform_idx[i] != platform_idx)
                ++j;
            else
                is_find = true;
            break;
        }
        if (is_find)
        {
            return m_platform_vel[j];
        }
        else
        {
            return -1;
        }
    }

    vector2f getHeroPosition()
    {
        return m_hero_pos;
    }

    vector2f getFinishPosition()
    {
        return m_finish_pos;
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

    std::vector<float> m_platform_vel;
    std::vector<std::pair<float, float>> m_borders;
    bool m_right_border;

    int m_platform_count;
    std::vector<size_t> m_platform_idx;

    vector2f m_finish_pos;
    vector2f m_hero_pos;

    sf::Texture m_texture;
};