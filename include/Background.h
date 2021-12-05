#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Background : public sf::Drawable, public sf::Transformable
{
public:
    Background();
    ~Background();

    void update(const sf::View&);

private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
    void loadTexture();

    sf::Texture m_texture;
    std::array<sf::Vertex, 8> m_vertices;
};