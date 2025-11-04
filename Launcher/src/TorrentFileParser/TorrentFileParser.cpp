#include "TorrentFileParser.hpp"

#include "Logger.hpp"

TorrentFileParser::TorrentFileParser(std::unique_ptr<IReadStrategy>&& readStrategy)
    : m_readStrategy(std::move(readStrategy))
{}

void TorrentFileParser::setReadStrategy(std::unique_ptr<IReadStrategy>&& readStrategy) noexcept
{
    m_readStrategy = std::move(readStrategy);
}

void TorrentFileParser::parse(const std::filesystem::path& pathToTorrentFile)
{
    if (m_readStrategy == nullptr)
    {
        LOGE(TorrentFileParser, "Cannot parse torrent file when no read strategy set");
        return;
    }
    LOGI(TorrentFileParser, "Parse Torrent File[{}]", pathToTorrentFile);

    m_bencodeParser.parse(m_readStrategy->read(pathToTorrentFile));
}
