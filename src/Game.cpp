#include "Game.h"

Game::Game() : m_sceneManager(SceneManager(&m_window))
{
    m_window.create(sf::VideoMode(800, 600), "AI_Takeover");
}

Game::~Game() {}

void Game::run()
{
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.0f / 60.0f);

    while (m_window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::sleep(frameTime - dt);

        m_sceneManager.handleEvents();
        m_sceneManager.handleInput();
        m_sceneManager.update(dt);

        m_window.clear(sf::Color::Black);
        m_sceneManager.draw();
        m_window.display();
    }
}
