#pragma once

#include "BencodeParser/BencodeParser.hpp"

#include "ReadStrategy/IReadStrategy.hpp"

class TorrentFileParser
{
public:
    TorrentFileParser() = default;
    explicit TorrentFileParser(std::unique_ptr<IReadStrategy>&& readStrategy);
    ~TorrentFileParser() = default;

    void setReadStrategy(std::unique_ptr<IReadStrategy>&& readStrategy) noexcept;

    void parse(const std::filesystem::path& pathToTorrentFile);

private:
    std::unique_ptr<IReadStrategy> m_readStrategy;

    BencodeParser m_bencodeParser;
};
