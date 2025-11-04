#pragma once

#include <vector>
#include <cstdint>

class IReadStrategy
{
public:
    IReadStrategy() = default;
    virtual ~IReadStrategy() = default;

    virtual std::vector<uint8_t> read() = 0;
};
