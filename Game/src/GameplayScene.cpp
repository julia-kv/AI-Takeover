#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow &w,
                             const size_t num_of_level,
                             Constants &constants,
                             SceneSwitcher &scn_switcher) : m_window(w),
                                                            m_level(w,
                                                                    num_of_level,
                                                                    constants.at("TILE_SIZE"),
                                                                    constants.at("PLATFORM_VELOCITY"),
                                                                    constants.at("HERO_VELOCITY"),
                                                                    constants.at("HERO_ACCELERATION")),
                                                            m_background("../Files/Background_" + std::to_string(num_of_level) + ".png"),
                                                            m_sceneSwitcher(scn_switcher)

{
}

GameplayScene::~GameplayScene()
{
}

void GameplayScene::handleEvents(const sf::Event &event)
{
    m_level.handleEvents(event);
}

void GameplayScene::handleInput()
{
    m_level.handleInput();
}

void GameplayScene::update(sf::Time dt)
{
    m_background.update(m_window.getView());
    m_level.update(dt);
    checkLevel();
}

void GameplayScene::draw() const
{
    m_window.draw(m_background);
    m_window.draw(m_level);
}

void GameplayScene::checkLevel()
{
    if (m_level.isFinished())
        m_sceneSwitcher.switchTo(SceneType::MAIN_MENU);
    else if (m_level.isDead())
        m_sceneSwitcher.switchTo(SceneType::MAIN_MENU);
}