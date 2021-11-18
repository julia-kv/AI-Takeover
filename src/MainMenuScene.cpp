#include "MainMenuScene.h"

MainMenuScene::MainMenuScene(sf::RenderWindow *w) : m_window(w)
{
    createButtons();
}

MainMenuScene::~MainMenuScene()
{
    m_buttons.clear();
}

void MainMenuScene::handleEvents()
{
}

SceneType MainMenuScene::handleInput()
{
    return SceneType::MAIN_MENU;
}

void MainMenuScene::update(sf::Time dt)
{
}

void MainMenuScene::draw()
{
}

void MainMenuScene::createButtons()
{
}

std::vector<Button>& MainMenuScene::getButtons()
{
    return m_buttons;
}