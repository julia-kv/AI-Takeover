#include "Game.h"
#include <iostream>
#include "Constants.h"

Game::Game()
{
    std::cout << "Game ctor()\n";
}

Game::~Game()
{
    std::cout << "Game dtor\n";
}

void Game::run()
{
    Constants constants;
    if (!constants.read_file())
        return;

    sf::RenderWindow window(sf::VideoMode(constants["SCREEN_INITIAL_WIDTH"], constants["SCREEN_INITIAL_HEIGHT"]),
                            "AI_Takeover");
    SceneManager sceneManager(&window);
    startGameLoop(window, sceneManager);
}

void Game::startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager)
{
    sf::Clock clock;
    sf::Time frameTime = sf::seconds(1.0f / 60.0f);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::sleep(frameTime - dt);

        sceneManager.handleEvents();
        sceneManager.handleInput();
        sceneManager.update(dt);

        window.clear(sf::Color::Black);
        sceneManager.draw();
        window.display();
    }
}