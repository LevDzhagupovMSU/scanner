#include "scan_result.hpp"
#include "type_file.hpp"

ScanResult::ScanResult(const std::filesystem::path& path_) : path{path_} {
    const static FileExtensionF fef;
    type = fef.checkFileType(path); 
};