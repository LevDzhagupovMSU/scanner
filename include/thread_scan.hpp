#pragma once

#include "header.hpp"
#include "type_file.hpp"
#include "scan_result.hpp"

class scanner_dir{
    std::filesystem::path home_dir_ = std::getenv("HOME");
    std::vector<std::filesystem::path> top_files_;
    std::atomic<bool> running_ = true;
    size_t num_th_;

    void scanCurDir(const std::filesystem::path& dir, 
                    std::vector<ScanResult>& exp_file, 
                    std::mutex& mutex, const FileExtensionF& fef) const;

    void stop();

public:
    scanner_dir(size_t num_th = 4);

    std::vector<ScanResult> find() const;
    void find_periodic(std::chrono::milliseconds period);

    void input();
};