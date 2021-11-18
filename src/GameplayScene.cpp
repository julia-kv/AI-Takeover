#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow *w, const std::string &fn) : m_window(w), m_level(Level(w, fn))
{
}

GameplayScene::~GameplayScene() {}

void GameplayScene::handleEvents() {}

SceneType GameplayScene::handleInput()
{
    return SceneType::GAMEPLAY;
}

void GameplayScene::update(sf::Time dt) {}

void GameplayScene::draw() {}