#include "Constants.h"

Constants::Constants() {}
Constants::~Constants() {}

bool Constants::read_file(const std::string &f_name/* =".config" */)
{
    std::string line;
    std::ifstream file(f_name);
    if (!file.is_open())
        return false;

    while (std::getline(file, line))
    {
        try
        {
            parse_line(line);
        }
        catch (const boost::bad_lexical_cast &e)
        {
            std::cerr << e.what() << " (File : '" << f_name << "' ; line : '" << line << ")'\n";
            return false;
        }
    }

    return true;
}

float Constants::operator[](const std::string &key)
{
    return m_map[key];
}

float Constants::at(const std::string &key) const
{
    return m_map.at(key);
}

void Constants::parse_line(const std::string &line)
{
    std::istringstream is_line(line);
    std::string key;
    float value = 0;
    if (std::getline(is_line, key, '='))
    {
        std::string str_value;
        is_line >> str_value;
        float value = boost::lexical_cast<float>(str_value);
        m_map[key] = value;
    }
}