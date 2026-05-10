#include "type_file.hpp"

bool FileExtensionF::checkType(const std::filesystem::path& file, FileType type) const{
    if(!std::filesystem::is_regular_file(file) || !file.has_extension()) return false;

    std::string extension = file.extension().string();
    for(const auto& pair : file_type){
        if(pair.first != type) continue;

        if (std::find(pair.second.begin(), pair.second.end(), extension) != pair.second.end()) {
            return true;
        }
    }

    return false;
}

FileType FileExtensionF::checkFileType(const std::filesystem::path& file) const{
    if(!std::filesystem::is_regular_file(file) || !file.has_extension()) 
        return FileType::unknown;

    std::string extension = file.extension().string();
    for(const auto& pair : file_type){
        if (std::find(pair.second.begin(), pair.second.end(), extension) != pair.second.end()) {
            return pair.first;
        }
    }

    return FileType::unknown;
}