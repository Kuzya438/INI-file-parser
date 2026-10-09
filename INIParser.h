#pragma once
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <type_traits>

class INIParser {
private:
    using section = std::map<std::string, std::string>;
    std::map<std::string, section> data;

    std::string trim(const std::string& s);

public:
    INIParser(const std::string& name);

    template <typename T>
    T get_value(const std::string& sec, const std::string& key) const {
        auto secIt{ data.find(sec) };
        if (secIt == data.end()) { throw std::runtime_error("Section not found: " + sec); }

        auto keyIt{ secIt->second.find(key) };
        if (keyIt == secIt->second.end()) {
            const section& s{ secIt->second };
            std::cout << "Perhaps you were looking for:" << std::endl;
            for (const auto& kv : s) {
                std::cout << sec << "." << kv.first << std::endl;
            }
            throw std::runtime_error("Key not found: " + sec + "." + key);
        }

        if constexpr (std::is_same_v<T, std::string>) {
            if (keyIt->second == "") { throw std::runtime_error("The variable value " + key + " was not found."); }
            return keyIt->second;
        }
        else {
            std::istringstream iss(keyIt->second);
            T value{};
            iss >> value;

            if (!iss) { throw std::runtime_error("The variable value " + key + " was not found."); }

            return value;
        }
    }
};