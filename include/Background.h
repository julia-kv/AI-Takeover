#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Background
{
public:
    Background(sf::RenderWindow *);
    ~Background();

    void draw();
    void update();

private:
    void loadTexture();

    sf::Texture m_texture;
    sf::Sprite m_sprite_left, m_sprite_center, m_sprite_right;
    sf::RenderWindow *m_window;
};