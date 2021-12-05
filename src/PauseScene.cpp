#include "PauseScene.h"
#include <iostream>

PauseScene::PauseScene(sf::RenderWindow *w) : m_window(w)
{
    std::cout << "PauseScene ctor(sf::RenderWindow *w)\n";
    createButtons();
}

PauseScene::~PauseScene()
{
    std::cout << "PauseScene dtor\n";
    m_buttons.clear();
}

void PauseScene::handleEvents(const sf::Event &event) {}

SceneType PauseScene::handleInput()
{
    return SceneType::PAUSE;
}

void PauseScene::update(sf::Time dt) {}

void PauseScene::draw()
{
}

void PauseScene::createButtons() {}

std::vector<Button> &PauseScene::getButtons()
{
    return m_buttons;
}