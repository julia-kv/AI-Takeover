#include "ChooseLevelMenuScene.h"
#include <iostream>

ChooseLevelMenuScene::ChooseLevelMenuScene(sf::RenderWindow &w, SceneManager *sm) : m_window(w), m_sceneManager(sm)
{
    createButtons();
}

ChooseLevelMenuScene::~ChooseLevelMenuScene()
{
}

void ChooseLevelMenuScene::handleEvents(const sf::Event &event)
{
}

SceneType ChooseLevelMenuScene::handleInput()
{
    return SceneType::CHOOSE_LEVEL_MENU;
}

SceneType ChooseLevelMenuScene::update(sf::Time dt)
{
    return SceneType::CHOOSE_LEVEL_MENU;
}

void ChooseLevelMenuScene::draw() const
{
}

void ChooseLevelMenuScene::createButtons()
{
}

std::vector<Button> &ChooseLevelMenuScene::getButtons()
{
    return m_buttons;
}