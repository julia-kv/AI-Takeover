#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SceneManager.h"

class Button
{
public:
    Button(sf::RenderWindow *w,
           sf::Vector2f size) : m_window(w)
    {
        m_rect = sf::RectangleShape(size);
        m_rect.setFillColor(sf::Color(179, 179, 255));
    }
    ~Button() {}

    void draw()
    {
        m_window->draw(m_rect);
        m_window->draw(m_text);
    }

    sf::Vector2f getPosition()
    {
        return m_rect.getPosition();
    }

    sf::Vector2f getSize()
    {
        return m_rect.getSize();
    }

    void setPosition(const sf::Vector2f& position)
    {
        m_rect.setPosition(position);
    }

    void setText(const std::string& str, sf::Font& font)
    {
        m_text.setFont(font);
        m_text.setString(str);
        m_text.setFillColor(sf::Color::White);

        m_text.setPosition(m_rect.getPosition() + sf::Vector2f(20, 0));
    }

private:
    sf::RenderWindow *m_window;
    sf::RectangleShape m_rect;
    sf::Text m_text;
};