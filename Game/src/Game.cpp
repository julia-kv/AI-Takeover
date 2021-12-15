#include "Game.h"
#include <iostream>
#include "Constants.h"

Game::Game() : frameTime(sf::seconds(1.f / 60.f))
{
}

Game::~Game()
{
}

void Game::run()
{
    Constants constants;
    if (!constants.read_file("../Files/.config"))
    {
        std::cerr << "Failed to read constants file\n";
        return;
    }

    sf::RenderWindow window;
    try
    {
        window.create(sf::VideoMode(constants.at("SCREEN_INITIAL_WIDTH"),
                                    constants.at("SCREEN_INITIAL_HEIGHT")),
                      "AI_Takeover",
                      sf::Style::Default);
    }
    catch (const std::out_of_range &)
    {
        std::cerr << "SCREEN_INITIAL_WIDTH or SCREEN_INITIAL_HEIGHT not found in constants\n";
        return;
    }

    SceneManager sceneManager(window, constants);
    startGameLoop(window, sceneManager);
}

void Game::startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager)
{
    sf::Clock clock;
    while (window.isOpen() &&
           loop(window, sceneManager, clock.restart()))
    {
    }
}

bool Game::loop(sf::RenderWindow &window, SceneManager &sceneManager, sf::Time dt)
{
    sf::sleep(frameTime - dt);

    if (sceneManager.cycle(dt))
        return false;
    window.clear(sf::Color::Black);
    sceneManager.draw();
    window.display();

    return true;
}