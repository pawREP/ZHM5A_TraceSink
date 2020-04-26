#pragma once

#include <fstream>
#include <string>
#include <filesystem>

class FileLogger {
private:
    mutable std::ofstream ofs;
    std::filesystem::path path_;

    std::filesystem::path getLogFile() const;

public:
    FileLogger();
    FileLogger(const FileLogger&) = delete;
    FileLogger(FileLogger&&) = delete;
    ~FileLogger();

    FileLogger& operator=(const FileLogger&) = delete;
    FileLogger& operator=(FileLogger&&) = delete;

    void write(const char* data, int dataLength) const;
    bool isOpen() const;
    const std::filesystem::path& path() const;
};