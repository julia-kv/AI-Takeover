#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"

class Button : public sf::Drawable, public sf::Transformable
{
public:
    Button(const std::string &str,
           const sf::Font &font,
           const sf::Texture &texture,
           const unsigned int characterSize = 30U) : m_text(str, font, characterSize),
                                                     m_sprite(texture)
    {
        m_sprite.setScale(2 * m_text.getLocalBounds().width / texture.getSize().x,
                          2 * (float)characterSize / texture.getSize().y);
    }

    ~Button() {}

    sf::Vector2f getPosition() const
    {
        return m_sprite.getPosition();
    }

    sf::Vector2f getSize() const
    {
        return sf::Vector2f(m_sprite.getGlobalBounds().width,
                            m_sprite.getGlobalBounds().height);
    }

    void setPosition(const sf::Vector2f &pos, const float windowWidth)
    {
        m_sprite.setPosition(pos);
        m_text.setPosition((windowWidth - m_text.getGlobalBounds().width) / 2, pos.y + m_text.getGlobalBounds().height / 2);
    }

    void setWidth(const float width)
    {
        m_sprite.scale(width / m_sprite.getGlobalBounds().width, 1.f);
    }

    bool isPressed(sf::Vector2f mousePos) const
    {
        return m_sprite.getGlobalBounds().contains(mousePos.x, mousePos.y);
    }

private:
    sf::Vector2f getTextSize() const
    {
        return sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        target.draw(m_sprite);
        target.draw(m_text);
    }

    sf::Sprite m_sprite;
    sf::Text m_text;
};