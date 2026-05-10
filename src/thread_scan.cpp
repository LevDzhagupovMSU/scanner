#include "thread_scan.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <mutex>
#include <stdexcept>
#include <thread> 
#include <nlohmann/json.hpp>

scanner_dir::scanner_dir(size_t num_th) :
                 num_th_{num_th}{

    for(const auto& file : std::filesystem::directory_iterator{home_dir_}){
        top_files_.push_back(file.path());
    }
};

void scanner_dir::scanCurDir(const std::filesystem::path& dir, 
                    std::vector<ScanResult>& exp_file, 
                    std::mutex& mutex, const FileExtensionF& fef) const{                  
    for(const auto& file : std::filesystem::directory_iterator{dir}){
        if(std::filesystem::is_symlink(file.path()))
            continue;

        if(fef.checkFileType(file.path()) != FileType::unknown) {
            std::lock_guard<std::mutex> lock(mutex);
            exp_file.push_back(file.path());
        } else if(std::filesystem::is_directory(file.path())) {
            scanCurDir(file.path(), exp_file, mutex, fef);
        }
    }
}

std::vector<ScanResult> scanner_dir::find() const{
    std::vector<ScanResult> files;
    std::mutex mutex;
    const static FileExtensionF fef;

    std::vector<std::thread> threads;
    for(size_t i = 0; i < top_files_.size(); ++i){
        const auto& file = top_files_[i];

        if(fef.checkFileType(file) != FileType::unknown){
            std::lock_guard<std::mutex> lock(mutex);
            files.push_back(file);
        }else if(std::filesystem::is_directory(file)){
            threads.emplace_back([&, file](){
                scanCurDir(file, files, mutex, fef);
            });

            if(threads.size() >= num_th_ || i == top_files_.size() - 1){
                for(auto& t : threads){
                    t.join();
                }

                threads.clear();
            }
        }
    }

    return files;
}

void scanner_dir::find_periodic(std::chrono::milliseconds period) {
    while(running_){
        auto files = find();

        nlohmann::json j;

        for(const auto& elem : files){
            switch(elem.type){
                case FileType::audio:
                    j["audio"].push_back(elem.path.filename().string());
                    break;

                case FileType::video:
                    j["video"].push_back(elem.path.filename().string());
                    break;

                case FileType::image:
                    j["images"].push_back(elem.path.filename().string());
                    break;

                default:
                    break;
            }
        }

        std::string path = std::filesystem::path(home_dir_) / ".media_files";
        std::ofstream file(path);
        if (file.is_open()) {
            file << j.dump(4);
            file.close();
        }else{
            throw std::runtime_error{"Failed to open"};
        }

        std::this_thread::sleep_for(period);
    }
}

void scanner_dir::input() {
    std::string line;
    while (running_) {
        std::getline(std::cin, line);
        if (line == "q" || line == "Q") {
            stop();
            break;
        }
    }
}

void scanner_dir::stop(){
    running_ = false;
}