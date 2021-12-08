#include "Map.h"

Map::Map() : m_right_border(false),
             m_platform_count(0)
{
    if (!m_texture.loadFromFile("texture.png")) {
        std::cout << "Failed to load texture.png file\n";
    }
}

void Map::readMap(const size_t num_of_level)
{
    readLevelFile("Level_" + std::to_string(num_of_level) + ".txt");
}

void Map::readLevelFile(const std::string &fn)
{
    std::string line;
    std::ifstream myfile(fn);
    if (!myfile.is_open()) {
        std::cout << "Failed to open level file \'" << fn << '\'' << std::endl;
        return;
    }

    size_t j = 0;
    size_t k = 0;

    while (!myfile.eof()) {
        getline(myfile, line);

        size_t num_tiles_x = line.size();
        k = std::max(k, num_tiles_x);

        for (int i = 0; i < num_tiles_x; ++i)
            if (line[i] != ' ')
                readTile(j, i, line[i]);

        ++j;
    }
    m_map_size.x = k;
    m_map_size.y = j;

}

void Map::readTile(int i, int j, char ch) {
    switch (ch) {

        case '*': {
            addTile(i, j, 0);
            break;
        }

        case '-': {
            addPlatform(i, j);
            break;
        }

        case '!': {
            vector2f finish_pos(j * m_tileSize, i * m_tileSize);
            m_finish_pos = finish_pos;
            break;
        }

        case 'h': {
            vector2f hero_pos(j * m_tileSize, i * m_tileSize);
            m_hero_pos = hero_pos;
            break;
        }

        default:
            break;
    }
}

void Map::addTile(int i, int j, int texture_num)
{
    sf::Vector2f pos0(j * m_tileSize, i * m_tileSize);
    sf::Vector2f pos1((j + 1) * m_tileSize, i * m_tileSize);
    sf::Vector2f pos2((j + 1) * m_tileSize, (i + 1) * m_tileSize);
    sf::Vector2f pos3(j * m_tileSize, (i + 1) * m_tileSize);

    sf::Vertex vert0(pos0);
    sf::Vertex vert1(pos1);
    sf::Vertex vert2(pos2);
    sf::Vertex vert3(pos3);

    vert0.texCoords = sf::Vector2f(0 + texture_num * 64, 0);
    vert1.texCoords = sf::Vector2f(64 + texture_num * 64, 0);
    vert2.texCoords = sf::Vector2f(64 + texture_num * 64, 64);
    vert3.texCoords = sf::Vector2f(0 + texture_num * 64, 64);

    m_vertices.push_back(vert0);
    m_vertices.push_back(vert1);
    m_vertices.push_back(vert2);
    m_vertices.push_back(vert3);

    ++m_platform_count;
}

void Map::addPlatform(int i, int j)
{
    if (!m_right_border) {
        addTile(i, j, 1);
        m_platform_idx.push_back(m_platform_count - 1);
        m_right_border = true;
    } else {
        auto platform_borders = std::make_pair(m_vertices[(m_platform_count - 1) * 4].position.x,
                                               (float) (j + 1) * m_tileSize);
        m_borders.push_back(platform_borders);
        m_platform_vel_arr.push_back(m_platform_vel);
        m_right_border = false;
    }
}

void Map::setSize(const float m_tile_size) {
    m_tileSize = m_tile_size;
}

void Map::setVelocity(const float v) {
    m_platform_vel = v;
}

void Map::update(sf::Time dt) {
    size_t j = 0;

    for (auto it: m_platform_idx) {

        if (m_vertices[it * 4].position.x <= m_borders[j].first) {
            m_platform_vel_arr[j] = m_platform_vel;
        }

        if (m_vertices[it * 4 + 2].position.x >= m_borders[j].second) {
            m_platform_vel_arr[j] = -1 * m_platform_vel;
        }

        vector2f del(m_platform_vel_arr[j] * dt.asSeconds(), 0);

        m_vertices[it * 4].position += del;
        m_vertices[it * 4 + 1].position += del;
        m_vertices[it * 4 + 2].position += del;
        m_vertices[it * 4 + 3].position += del;

        ++j;
    }
}

sf::Vector2i Map::getSize() {
    return m_map_size;
}

std::vector<sf::Vertex> &Map::getVertexArray() {
    return m_vertices;
}

bool Map::isPlatformMoving(int platform_idx) {
    if (platform_idx == -1)
        return false;

    for (size_t i = 0; i < m_platform_idx.size(); ++i) {
        if (m_platform_idx[i] == platform_idx)
            return true;
    }
    return false;
}

vector2f Map::getPlatformPosition(int platform_idx) {
    return vector2f(m_vertices[platform_idx * 4].position.x,
                    m_vertices[platform_idx * 4].position.y - m_tileSize);
}

float Map::getPlatformVel(int platform_idx) {
    int j = 0;
    bool is_find = false;
    for (size_t i = 0; i < m_platform_idx.size(); ++i) {
        if (m_platform_idx[i] != platform_idx)
            ++j;
        else {
            is_find = true;
            break;
        }
    }
    if (is_find) {
        return m_platform_vel_arr[j];
    } else {
        return -1;
    }
}

vector2f Map::getHeroPosition() {
    return m_hero_pos;
}

vector2f Map::getFinishPosition() {
    return m_finish_pos;
}

void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &m_texture;
    target.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);
}

