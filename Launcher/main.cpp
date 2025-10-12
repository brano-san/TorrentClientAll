#include <quill/std/FilesystemPath.h>
#include "Logger.hpp"

#include <filesystem>

int main(int argc, char *argv[])
{
    LOG_INFO(Core, "Program started from {}", std::filesystem::current_path());
    return 0;
}
