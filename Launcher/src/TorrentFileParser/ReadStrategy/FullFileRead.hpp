#pragma once

#include "IReadStrategy.hpp"

class FullFileReadStrategy: public IReadStrategy
{
public:
    virtual std::string read(const std::filesystem::path& pathToFile) override;

private:
    static constexpr uint64_t kMaxFileSizeToRead = 1'000'000;
};
