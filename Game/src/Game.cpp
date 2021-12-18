#include "Game.h"
#include <iostream>
#include "Constants.h"

Game::Game() : frameTime(sf::seconds(1.f / 60.f))
{
}

Game::~Game()
{
}

void Game::run() const noexcept
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
    if (sceneManager.successfullyInitialized())
        startGameLoop(window, sceneManager);
}

void Game::startGameLoop(sf::RenderWindow &window, SceneManager &sceneManager) const noexcept
{
    sf::Clock clock;
    while (window.isOpen() &&
           loop(window, sceneManager, clock.restart()))
    {
    }
}

bool Game::loop(sf::RenderWindow &window, SceneManager &sceneManager, const sf::Time dt) const noexcept
{
    // true if success
    // false if error

    sf::sleep(frameTime - dt);

    window.clear(sf::Color::Black);
    sceneManager.draw();
    window.display();

    return sceneManager.cycle(dt);
}