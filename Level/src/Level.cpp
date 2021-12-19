#include "Level.h"
#include <string>
#include <fstream>
#include <iostream>

Level::Level(sf::RenderWindow &w,
             const size_t num_of_level,
             const float tile_size,
             const float v_platform,
             const float v_hero,
             const float a_hero) : m_window(w),
                                   m_map(tile_size,
                                         v_platform),
                                   m_hero(tile_size,
                                          v_hero,
                                          a_hero),
                                   m_finish(tile_size),
                                   m_camera(w, m_hero),
                                   m_level_num(num_of_level) {
    readScoreFile(num_of_level);
    readLevelFile(num_of_level);
    m_camera.setMaxSize(m_map.getSize().x * tile_size);
}

Level::~Level() {



}

void Level::handleEvents(const sf::Event &event) {
    switch (event.type) {
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::Left ||
                event.key.code == sf::Keyboard::Right ||
                event.key.code == sf::Keyboard::Up ||
                event.key.code == sf::Keyboard::Down)
                m_hero.keyReleased(event.key.code);
            break;

        default:
            break;
    }
}

void Level::handleInput() {
    m_hero.handleInput();
}

void Level::update(sf::Time dt) {
    m_map.update(dt);
    m_hero.update(dt);
    m_camera.update();
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_map);
    target.draw(m_finish);
    target.draw(m_hero);
}

void Level::readLevelFile(const size_t num_of_level) {
    m_map.setScore(m_best_score);
    m_map.setGameTime(m_best_game_time);
    m_map.readMap(num_of_level);

    m_hero.setMap(&m_map);
    m_hero.setInitialPosition(m_map.getHeroPosition());

    m_finish.setPosition(m_map.getFinishPosition());
}

void Level::readScoreFile(const size_t num_of_level) {
    std::string line;
    std::ifstream file("../Files/results.txt");
    if (!file.is_open())
        std::cout << "Failed to read file ../Files/results.txt\n";

    bool find_score = false;
    bool find_time = false;

    while (std::getline(file, line)) {

        std::istringstream is_line(line);
        std::string key;
        std::getline(is_line, key, '=');

        if (key == ("BEST_SCORE_" + std::to_string(num_of_level))) {
            std::string str_value;
            is_line >> str_value;
            m_best_score = std::atoi(str_value.c_str());
            find_score = true;
        } else if (key == ("BEST_TIME_" + std::to_string(num_of_level))) {
            std::string str_value;
            is_line >> str_value;
            m_best_game_time = std::atof(str_value.c_str());
            find_time = true;
        } else {
            std::string str_value;
            is_line >> str_value;
        }
    }
    if (!find_score)
        m_best_score = 0;
    if (!find_time)
        m_best_game_time = 0.0f;

    file.close();
}


Map &Level::getMap() {
    return m_map;
}

Hero &Level::getHero() {
    return m_hero;
}

Finish &Level::getFinish() {
    return m_finish;
}

bool Level::isFinished() {

    if (m_hero.isFinished()) {
        changeScore();
    }
    return  m_hero.isFinished();
}

bool Level::isDead() {
    return m_hero.isDead();
}

void Level::changeScore() {

    if ((m_best_score < m_map.getScore() && m_best_game_time >= m_map.getGameTime()) ||
        (m_best_game_time == m_map.getScore() && m_best_game_time > m_map.getGameTime())) {

        std::string line;

        std::ifstream file("../Files/results.txt");
        if (!file.is_open())
            std::cout << "Failed to read file ../Files/results.txt\n";

        std::vector<std::string> all_str;

        while (std::getline(file, line)) {

            std::istringstream is_line(line);
            std::string key;
            std::getline(is_line, key, '=');

            if ((key == ("BEST_SCORE_" + std::to_string(m_level_num))) &&
                m_best_score < m_map.getScore()) {
                std::string str_value;
                is_line >> str_value;
                key += "=";
                key += std::to_string(m_map.getScore());
                all_str.push_back(key);

            } else if ((key == ("BEST_TIME_" + std::to_string(m_level_num))) &&
                       m_best_game_time > m_map.getGameTime()) {
                std::string str_value;
                is_line >> str_value;
                key += "=";
                key += std::to_string(m_map.getGameTime());
                all_str.push_back(key);

            } else {
                std::string str_value;
                is_line >> str_value;
                key += "=";
                key += str_value;
                all_str.push_back(key);
            }
        }

        file.close();

        std::ofstream file_new;
        file_new.open("../Files/results.txt", std::ofstream::trunc);

        for (auto const &s: all_str) {
            file_new << s << std::endl;
        }

        file.close();

        all_str.clear();
    }
}