#include "Background.h"
#include <iostream>

Background::Background(sf::RenderWindow *w) : m_window(w)
{
    std::cout << "Background(sf::RenderWindow *w) ctor\n";
    loadTexture();
}

Background::~Background()
{
    std::cout << "Background dtor\n";
}

void Background::draw()
{
    m_window->draw(m_sprite_left);
    m_window->draw(m_sprite_center);
    m_window->draw(m_sprite_right);
}

void Background::update()
{
    if (m_window->getView().getCenter().x < m_sprite_center.getPosition().x)
    {
        m_sprite_right.setPosition(m_sprite_center.getPosition());
        m_sprite_center.setPosition(m_sprite_left.getPosition());
        m_sprite_left.setPosition(m_sprite_center.getPosition().x - 800.0f, m_sprite_center.getPosition().y);
    }
    else if (m_window->getView().getCenter().x > m_sprite_right.getPosition().x)
    {
        m_sprite_left.setPosition(m_sprite_center.getPosition());
        m_sprite_center.setPosition(m_sprite_right.getPosition());
        m_sprite_right.setPosition(m_sprite_center.getPosition().x + 800.0f, m_sprite_center.getPosition().y);
    }
}

void Background::loadTexture()
{
    if (!m_texture.loadFromFile("background.png"))
    {
        std::cout << "Failed to load background texture from file background.jpg\n";
    }
    
    m_sprite_left.setTexture(m_texture);
    m_sprite_center.setTexture(m_texture);
    m_sprite_right.setTexture(m_texture);

    m_sprite_left.setPosition(-800, 0);
    m_sprite_center.setPosition(0, 0);
    m_sprite_right.setPosition(800, 0);
}