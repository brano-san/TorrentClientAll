#include <quill/std/FilesystemPath.h>
#include "Logger.hpp"

#include <filesystem>

#include <GenEnum.hpp>

class BencodedDictionary
{
    GENENUM(uint8_t, Fields, Announce, AnnounceList, Info, CreationDate, Comment, CreatedBy, Encoding);
public:
private:
    std::unordered_map<Fields, std::string_view> m_field
};

int main(int argc, char *argv[])
{
    LOG_INFO(Core, "Program started from {}", std::filesystem::current_path());
    return 0;
}
