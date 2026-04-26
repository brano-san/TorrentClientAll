#include "Logger.hpp"

#include <filesystem>

#include "TorrentFileParser/TorrentFileParser.hpp"
#include "TorrentFileParser/ReadStrategy/FullFileRead.hpp"

int main(int argc, char* argv[])
{
    LOGI(Core, "Program started from {}", std::filesystem::current_path());
    for (uint32_t i = 0; i < static_cast<uint32_t>(argc); ++i)
    {
        const std::string str{argv[i]};
        LOGI(Core, "Argc - {}; Argv[{}] - {}", argc, i, str);
    }

    TorrentFileParser torrentParser{std::make_unique<FullFileReadStrategy>()};
    torrentParser.parse(std::filesystem::current_path().append("hades.torrent"));

    int32_t a;
    std::cin >> a;
    return 0;
}
