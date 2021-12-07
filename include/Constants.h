#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <unordered_map>
#include <iostream>

class Constants
{
public:
    Constants();
    ~Constants();

    bool read_file(const std::string &f_name = ".config");
    float operator[](const std::string &key);
    float at(const std::string &key) const;

private:
    void parse_line(const std::string &line);
    std::unordered_map<std::string, float> m_map;
};