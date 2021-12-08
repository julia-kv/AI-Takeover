#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

enum class State {PLAYING, DIED, FINISHED};

class Hero : public sf::Drawable, public sf::Transformable
{
    float tile_size = 40.0f;
    float m_hero_vel = 300.0f;
    float m_y_koef = 1.5f;
    float m_acceleration = 1000.0f;


public:

    Hero()
    {

        if (!m_texture.loadFromFile("человек.png"))
        {
            std::cout << "Failed to read file hero.png\n";
        }

        m_sprite.setTexture(m_texture);
        m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 64));
        m_sprite.setScale(tile_size / 32, 2 * tile_size / 64);

        m_vel.x = 0;
        m_vel.y = 0;

        m_state = State::PLAYING;
        m_is_jump = true;
        m_idx_platform = -1;//is_flying
        m_vel.y = m_acceleration;
        m_changes = 0;
    }
    ~Hero(){};

    void setSize(const float tile_size)
    {
        m_tileSize = tile_size;
        m_halfTileSize = tile_size / 2;
        m_sprite.setScale(tile_size / 40, tile_size / 40);
    }

    void setVelocity(const float v)
    {
        m_hero_vel = v;
    }

    void setAcceleration(const float a)
    {
        m_acceleration = a;
    }

    sf::Vector2f getPosition()
    {
        return m_sprite.getPosition();
    }

    void setInitialPosition(sf::Vector2f pos)
    {
        m_sprite.setPosition(pos);
    }

    void keyReleased(sf::Keyboard::Key code) {
        if (code == sf::Keyboard::Left || code == sf::Keyboard::Right)
            m_vel.x = 0;
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            m_vel.x = m_hero_vel;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            m_vel.x = -1 * m_hero_vel;

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && !m_is_jump)
        {
            m_vel.y = -1 * m_hero_vel * m_y_koef;
            m_is_jump = true;
        }
    }

    void update(sf::Time dt)
    {
        if (m_is_jump)
            m_vel.y += m_acceleration * dt.asSeconds();

        if (isReachFinish())
            m_state = State::FINISHED;

        if (m_sprite.getPosition().y > m_window_size.y + 5 * tile_size)
            m_state = State::DIED;

        sf::Vector2f del = m_vel * dt.asSeconds();

        if (m_map->isPlatformMoving(m_idx_platform)) //&& !m_is_jump)
        {
            float platform_vel = m_map->getPlatformVel(m_idx_platform);

            float del_x = platform_vel * dt.asSeconds();
            del.x += del_x;
        }

        move(del);
        changeDirection(dt);
    }

    void setMap(Map *map)
    {
        m_map = map;
        m_window_size = sf::Vector2f(m_map->getSize().x * tile_size, m_map->getSize().y * tile_size);
    }

    bool isFinished()
    {
        return (m_state == State::FINISHED);
    }

    bool isDead()
    {
        return (m_state == State::DIED);
    }

private:

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite);
    }

    void changeDirection(sf::Time dt) {

        if (m_vel.x > 0)
        {
            if (m_changes > 0.35) {
                if (m_sprite.getTextureRect().left == 64)
                {
                    m_sprite.setTextureRect(sf::IntRect(32, 0, 32, 64));
                    m_changes = 0;
                }
                else {
                    m_sprite.setTextureRect(sf::IntRect(64, 0, 32, 64));
                    m_changes = 0;
                }
            } else {
                if (m_sprite.getTextureRect().left == 64)
                    m_sprite.setTextureRect(sf::IntRect(64, 0, 32, 64));
                else
                    m_sprite.setTextureRect(sf::IntRect(32, 0, 32, 64));
                m_changes += dt.asSeconds();
            }
        }

        else if (m_vel.x < 0)
        {
            if (m_changes > 0.35) {
                if (m_sprite.getTextureRect().left == 96)
                {
                    m_sprite.setTextureRect(sf::IntRect(128, 0, 32, 64));
                    m_changes = 0;

                }
                else {
                    m_sprite.setTextureRect(sf::IntRect(96, 0, 32, 64));
                    m_changes = 0;
                }
            } else {
                if (m_sprite.getTextureRect().left == 96)
                    m_sprite.setTextureRect(sf::IntRect(96, 0, 32, 64));
                else
                    m_sprite.setTextureRect(sf::IntRect(128, 0, 32, 64));
                m_changes += dt.asSeconds();
            }
        }

        else {
            m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 64));
            m_changes = 0;
        }
    }

    void move(sf::Vector2f del) {
        if (del.x > 0)
            del.x = std::min(del.x, m_halfTileSize);
        else
            del.x = std::max(del.x, -m_halfTileSize);

        if (del.y > 0)
            del.y = std::min(del.y, m_halfTileSize);
        else
            del.y = std::max(del.y, -m_halfTileSize);

        move_x(del.x);
        move_y(del.y);
    }

    void move_x(float dx) {

        m_sprite.move(dx, 0);

        float rect_left = m_sprite.getPosition().x;
        float rect_right = m_sprite.getPosition().x + m_sprite.getTextureRect().width * m_sprite.getScale().x;
        float rect_top = m_sprite.getPosition().y;
        float rect_bottom = m_sprite.getPosition().y + m_sprite.getTextureRect().height * m_sprite.getScale().y;

        std::vector<sf::Vertex> vertices = m_map->getVertexArray();

        for (int i = 0; i < vertices.size(); i += 4) {
            float tile_left = vertices[i].position.x;
            float tile_right = vertices[i + 2].position.x;
            float tile_top = vertices[i].position.y;
            float tile_bottom = vertices[i + 2].position.y;

            if ((rect_top < tile_bottom && tile_bottom < rect_bottom) ||
                (rect_top < tile_top && tile_top < rect_bottom) ||
                (rect_top == tile_top && rect_bottom == tile_bottom)) {

                if (dx > 0) {

                    if (rect_left < tile_left && tile_left < rect_right)
                        m_sprite.setPosition(tile_left - tile_size, rect_top);

                } else if (dx < 0) {

                    if (rect_left < tile_right && tile_right < rect_right)
                        m_sprite.setPosition(tile_right, rect_top);

                } else {

                    if (rect_left < tile_left && tile_left < rect_right)
                        m_sprite.setPosition(tile_left - tile_size, rect_top);

                    if (rect_left < tile_right && tile_right < rect_right)
                        m_sprite.setPosition(tile_right, rect_top);
                }
            }
        }
    }

    void move_y(float dy) {
        if (dy == 0)
            return;

        m_is_jump = true;
        m_sprite.move(0, dy);

        float rect_left = m_sprite.getPosition().x;
        float rect_right = m_sprite.getPosition().x + m_sprite.getTextureRect().width * m_sprite.getScale().x;
        float rect_top = m_sprite.getPosition().y;
        float rect_bottom = m_sprite.getPosition().y + m_sprite.getTextureRect().height * m_sprite.getScale().y;

        std::vector<sf::Vertex> vertices = m_map->getVertexArray();
        int platform_idx = -1;

        for (int i = 0; i < vertices.size(); i += 4) {
            float tile_left = vertices[i].position.x;
            float tile_right = vertices[i + 2].position.x;
            float tile_top = vertices[i].position.y;
            float tile_bottom = vertices[i + 2].position.y;

            if ((rect_left < tile_right && tile_right < rect_right) ||
                (rect_left < tile_left && tile_left < rect_right) ||
                (rect_left == tile_left && rect_right && tile_right)) {

                if (dy > 0) {

                    if (rect_top < tile_top && tile_top < rect_bottom) {
                        m_sprite.setPosition(rect_left, tile_top - 2 * tile_size);
                        m_is_jump = false;
                        platform_idx = i / 4;
                    }

                } else {

                    if (rect_top < tile_bottom && tile_bottom < rect_bottom) {
                        m_sprite.setPosition(rect_left, tile_bottom);
                        m_vel.y = 0;
                        platform_idx = i / 4;
                    }
                }
            }
        }
        m_idx_platform = platform_idx;
    }

    bool isReachFinish() {

        float rect_left = m_sprite.getPosition().x;
        float rect_right = m_sprite.getPosition().x + tile_size;
        float rect_top = m_sprite.getPosition().y;
        float rect_bottom = m_sprite.getPosition().y + tile_size * 2;

        float finish_left = m_map->getFinishPosition().x;
        float finish_right = finish_left + tile_size;
        float finish_top = m_map->getFinishPosition().y;
        float finish_bottom = finish_top + tile_size;

        if (((rect_left >= finish_left && rect_left < finish_right) ||
             (rect_right <= finish_right && rect_right > finish_left)) &&
            ((rect_bottom >= finish_bottom && rect_bottom < finish_top) ||
             (rect_top <= finish_top && rect_top > finish_bottom)))
            return true;

        else return false;
    }

    sf::Vector2f m_vel;
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    float m_changes;

    bool m_is_jump;
    State m_state;

    int m_idx_platform;

//    float m_hero_vel, m_acceleration;
    Map *m_map;
    sf::Vector2f m_window_size;
};

