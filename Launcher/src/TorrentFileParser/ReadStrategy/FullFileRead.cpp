#include "FullFileRead.hpp"

#include <fstream>

#include "Logger.hpp"

std::string FullFileReadStrategy::read(const std::filesystem::path& pathToFile)
{
    namespace fs = std::filesystem;

    if (!fs::exists(pathToFile))
    {
        LOGVE(FullFileReadStrategy, "File does not exist: {}", pathToFile);
        return {};
    }
    if (fs::is_directory(pathToFile))
    {
        LOGVE(FullFileReadStrategy, "Given path is a directory: {}", pathToFile);
        return {};
    }
    if (!static_cast<bool>(fs::status(pathToFile).permissions() & fs::perms::owner_read))
    {
        LOGVE(FullFileReadStrategy, "No read permission for file: {}", pathToFile);
        return {};
    }

    const auto fileSize = fs::file_size(pathToFile);
    if (fileSize > kMaxFileSizeToRead)
    {
        LOGVE(FullFileReadStrategy, "File size more than expected Limit[{}], File[{}]", kMaxFileSizeToRead, pathToFile);
        return {};
    }

    std::ifstream file;
    file.open(pathToFile, std::ios::in | std::ios::binary);
    if (!file.is_open())
    {
        LOGVE(FullFileReadStrategy, "Cannot open file[{}]; Error[{}]", pathToFile, std::strerror(errno));
        return {};
    }

    std::string content(fileSize, '\0');
    if (!file.read(content.data(), static_cast<std::streamsize>(fileSize)))
    {
        LOGVE(FullFileReadStrategy, "Cannot read from file[{}]; Error[{}]", pathToFile, std::strerror(errno));
        return {};
    }
    return content;
}
