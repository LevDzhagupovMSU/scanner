#pragma once

#include "type_file.hpp"
#include <filesystem>


struct ScanResult{
    FileType type;
    std::filesystem::path path; 

    ScanResult(const std::filesystem::path& path_);
};