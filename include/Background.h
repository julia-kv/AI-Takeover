#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

enum RelativePosition
{
    LEFT_HALF,
    RIGHT_HALF,
    OUTSIDE,
    START
};

class Background : public sf::Drawable, public sf::Transformable
{
public:
    Background(const std::string &);
    ~Background();

    void update(const sf::View &);

private:
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const;
    void loadTexture(const std::string &);
    RelativePosition findPosition(const sf::View &);

    sf::Texture m_texture;
    std::array<sf::Vertex, 8> m_vertices;
    RelativePosition m_previousPosition;
};