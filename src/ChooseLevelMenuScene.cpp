#include "ChooseLevelMenuScene.h"

ChooseLevelMenuScene::ChooseLevelMenuScene(sf::RenderWindow *w, SceneManager *sm) : m_window(w), m_sceneManager(sm)
{
    createButtons();
}

ChooseLevelMenuScene::~ChooseLevelMenuScene()
{
    m_buttons.clear();
}

void ChooseLevelMenuScene::handleEvents()
{
}

SceneType ChooseLevelMenuScene::handleInput()
{
    return SceneType::CHOOSE_LEVEL_MENU;
}

void ChooseLevelMenuScene::update(sf::Time dt)
{
}

void ChooseLevelMenuScene::draw()
{
}

void ChooseLevelMenuScene::createButtons()
{
}

std::vector<Button>& ChooseLevelMenuScene::getButtons()
{
    return m_buttons;
}