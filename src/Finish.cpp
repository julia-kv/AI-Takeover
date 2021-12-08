#include "Finish.h"

Finish::Finish() {

    if (!m_texture.loadFromFile("finish.png"))
    {
        std::cout << "Failed to read file finish.png\n";
    }

    m_sprite.setTexture(m_texture);
//    m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 64));
    m_sprite.setScale(tile_size / 32, tile_size / 32);

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

void Finish::update(sf::Time dt) {}