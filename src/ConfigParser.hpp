#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class ConfigParser
{
public:
    struct Data
    {
        std::unordered_map<std::string, std::string> m_cvars;
    };

    enum class LoadResult
    {
        OK,
        MISSING,
        ERROR
    };

    LoadResult load(const std::string& path, Data& out) const;

private:
    static std::string toUpper(std::string value);
    static std::string stripComment(const std::string& line);
    static std::vector<std::string> splitTokens(const std::string& line);
    static bool tryGenerateConfig(const std::string& path);
};
