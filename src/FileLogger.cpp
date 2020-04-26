#include "FileLogger.h"
#include <filesystem>

std::filesystem::path FileLogger::getLogFile() const {
    const auto logDir = std::filesystem::current_path() / "TraceSink/";

    if (!std::filesystem::exists(logDir))
        std::filesystem::create_directory(logDir);

    int id = 0;
    std::filesystem::path logFilePath;
    do {
        logFilePath = logDir / std::filesystem::path("trace_" + std::to_string(id) + ".log");
        ++id;
    } while (std::filesystem::exists(logFilePath));

    return logFilePath;
}

FileLogger::FileLogger() {
    path_ = getLogFile();
    ofs.open(path_);
}

FileLogger::~FileLogger() {
    if (ofs.is_open())
        ofs.close();
}

void FileLogger::write(const char* data, int dataLength) const {
    if (dataLength == 0)
        return;

    ofs.write(data, dataLength);
    ofs.write("\n", 1);
}

bool FileLogger::is_open() const {
    return ofs.is_open();
}

const std::filesystem::path& FileLogger::path() const {
    return path_;
}
