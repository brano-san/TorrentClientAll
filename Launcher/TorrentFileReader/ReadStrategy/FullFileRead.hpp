#pragma once

#include "IReadStrategy.hpp"

class TorrentFileReaderStrategy : IReadStrategy
{
public:
    TorrentFileReaderStrategy() = default;
    ~TorrentFileReaderStrategy() = default;

    std::vector<uint8_t> read() override;
};
