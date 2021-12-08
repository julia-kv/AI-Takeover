#include "Finish.h"

Finish::Finish() 
{

    if (!m_texture.loadFromFile("finish.png"))
    {
        std::cout << "Failed to read file finish.png\n";
    }

    m_sprite.setTexture(m_texture);
}

Finish::~Finish() {}

void Finish::setPosition(sf::Vector2f pos)
{
    m_sprite.setPosition(pos);
}

vector2f Finish::getPosition()
{
    return m_sprite.getPosition();
}

void Finish::setSize(const float tile_size)
{
    m_tileSize = tile_size;
    m_halfTileSize = tile_size / 2;
    m_sprite.setScale(tile_size / m_texture.getSize().x, tile_size / m_texture.getSize().y);
}

void Finish::update(sf::Time dt) {}