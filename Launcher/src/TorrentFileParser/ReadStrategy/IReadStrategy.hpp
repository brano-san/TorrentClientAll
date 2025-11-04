#pragma once

#include <string>

#include <filesystem>

class IReadStrategy
{
public:
    IReadStrategy()          = default;
    virtual ~IReadStrategy() = default;

    virtual std::string read(const std::filesystem::path& pathToFile) = 0;
};
