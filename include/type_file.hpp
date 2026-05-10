#pragma once

#include <unordered_map>
#include <vector>
#include <filesystem>
#include <algorithm>

enum class FileType{audio, video, image, unknown};

struct FileExtensionF{
    std::unordered_map<FileType, std::vector<std::string>> 
        file_type = {
            {FileType::audio, {".mp3", ".wav"}},
            {FileType::image, {".jpeg", ".png"}},
            {FileType::video, {".mpg"}}
        };
public:
    bool checkType(const std::filesystem::path& file, FileType type) const;

    FileType checkFileType(const std::filesystem::path& file) const;
};