#include "Game.h"
#include <iostream>

Game::Game() : m_sceneManager(&m_window)
{
    std::cout << "Game ctor()\n";
    m_window.create(sf::VideoMode(800, 600), "AI_Takeover");
}

Game::~Game()
{
    std::cout << "Game dtor\n";
}

void Game::run()
{
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.0f / 60.0f);

    while (m_window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::sleep(frameTime - dt);

        handleEvents();
        m_sceneManager.handleInput();
        m_sceneManager.update(dt);

        m_window.clear(sf::Color::Black);
        m_sceneManager.draw();
        m_window.display();
    }
}

void Game::handleEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;

        case sf::Event::KeyReleased:
            m_sceneManager.handleEvents(event);
            break;

        default:
            break;
        }
    }
}
