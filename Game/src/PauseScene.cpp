#include "PauseScene.h"
#include <iostream>

PauseScene::PauseScene(sf::RenderWindow &w, SceneSwitcher &scn_switcher) : m_window(w), m_sceneSwitcher(scn_switcher)
{
    createButtons();
}

PauseScene::~PauseScene()
{
}

void PauseScene::handleEvents(const sf::Event &event) {}

void PauseScene::handleInput()
{
}

void PauseScene::update(sf::Time dt)
{
}

void PauseScene::draw() const
{
}

void PauseScene::createButtons() {}

std::vector<Button> &PauseScene::getButtons()
{
    return m_buttons;
}