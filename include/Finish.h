#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>

typedef sf::Vector2<float> vector2f;

class Finish : public sf::Drawable, public sf::Transformable
{

    float tile_size = 40.0f;

public:
    Finish();

    ~Finish();

    void setPosition(vector2f pos);

    sf::Vector2f getPosition();

    void update(sf::Time);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite);
    }

    sf::Texture m_texture;
    sf::Sprite m_sprite;

    sf::RenderWindow *m_window;
};