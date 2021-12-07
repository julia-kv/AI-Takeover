#include "ChooseLevelMenuScene.h"
#include <iostream>

ChooseLevelMenuScene::ChooseLevelMenuScene(sf::RenderWindow *w, SceneManager *sm) : m_window(w), m_sceneManager(sm)
{
    std::cout << "ChooseLevelMenuScene ctor(sf::RenderWindow *w, SceneManager *sm)\n";
    createButtons();
}

ChooseLevelMenuScene::~ChooseLevelMenuScene()
{
    std::cout << "ChooseLevelMenuScene dtor\n";
    m_buttons.clear();
}

void ChooseLevelMenuScene::handleEvents(const sf::Event& event)
{
}

SceneType ChooseLevelMenuScene::handleInput()
{
    return SceneType::CHOOSE_LEVEL_MENU;
}

void ChooseLevelMenuScene::update(sf::Time dt)
{
}

void ChooseLevelMenuScene::draw() const
{
}

void ChooseLevelMenuScene::createButtons()
{
}

std::vector<Button>& ChooseLevelMenuScene::getButtons()
{
    return m_buttons;
}