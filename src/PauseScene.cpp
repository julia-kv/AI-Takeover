#include "PauseScene.h"

PauseScene::PauseScene(sf::RenderWindow *w) : m_window(w)
{
    createButtons();
}

PauseScene::~PauseScene()
{
    m_buttons.clear();
}

void PauseScene::handleEvents() {}

SceneType PauseScene::handleInput()
{
    return SceneType::PAUSE;
}

void PauseScene::update(sf::Time dt) {}

void PauseScene::draw() {}

void PauseScene::createButtons() {}

std::vector<Button>& PauseScene::getButtons()
{
    return m_buttons;
}