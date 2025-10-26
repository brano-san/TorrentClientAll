#include <quill/std/FilesystemPath.h>
#include "Logger.hpp"

#include <filesystem>

#include <GenEnum.hpp>

class BencodedDictionary
{
    GENENUM(uint8_t, Fields, Announce, AnnounceList, Info, CreationDate, Comment, CreatedBy, Encoding);

public:
private:
    std::unordered_map<Fields, std::string_view> m_field;
};

int main(int argc, char* argv[])
{
    LOG_INFO(Core, "Program started from {}", std::filesystem::current_path());
    for (uint32_t i = 0; i < argc; ++i)
    {
        const std::string str{argv[i]};
        LOG_INFO(Core, "Argc - {}; Argv[{}] - {}", argc, i, str);
    }

    int32_t a;
    std::cin >> a;
    return 0;
}
