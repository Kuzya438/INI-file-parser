#include "INIParser.h"
#include <fstream>

std::string INIParser::trim(const std::string& s) {
    auto start{ s.find_first_not_of(" \t\r\n") };
    if (start == std::string::npos) { return ""; }
    auto end{ s.find_last_not_of(" \t\r\n") };
    return s.substr(start, end - start + 1);
}

INIParser::INIParser(const std::string& name) {
    std::string line;
    std::string currentSection{};
    std::ifstream file(name, std::ios::in);

    if (!file.is_open()) { throw(std::runtime_error("ERROR! The file didn`t open.")); }

    unsigned short counter{};
    while (std::getline(file, line)) {
        std::string cleanStr{ trim(line) };
        ++counter;

        if (cleanStr.empty() || cleanStr[0] == ';') { continue; }
        if (cleanStr[0] == '[') {
            auto close{ cleanStr.find(']') };
            if (close == std::string::npos) { continue; }

            currentSection = trim(cleanStr.substr(1, close - 1));

            data.emplace(currentSection, section{});
            continue;
        }

        auto el{ cleanStr.find('=') };
        if (el == std::string::npos) { throw(std::runtime_error("ERROR! Incorrect syntax in line " + std::to_string(counter) + ".")); }
        std::string key{ trim(cleanStr.substr(0, el)) };

        if (key.empty()) { continue; }

        std::string val;
        auto stop{ cleanStr.find(';') };
        if (stop == std::string::npos) { val = trim(cleanStr.substr(el + 1)); }
        else { val = trim(cleanStr.substr(el + 1, stop - el - 2)); }

        data[currentSection][key] = val;
    }
    file.close();
}