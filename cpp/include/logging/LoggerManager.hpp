#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <mutex>
#include <vector>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/async.h>
#include <zmq.hpp>

// Logger manager class
class LoggerManager {
public:
    LoggerManager(const LoggerManager&) = delete;
    LoggerManager& operator=(const LoggerManager&) = delete;

    static LoggerManager& instance();

    void initialize(
        const std::string& defaultLogsDir = "logs",
        spdlog::level::level_enum defaultLevel = spdlog::level::info
    );

    std::shared_ptr<spdlog::logger> createLogger(
        const std::string& name,
        spdlog::level::level_enum level = spdlog::level::info,
        size_t maxFileSize = 1024 * 1024 * 10,
        size_t maxFiles = 5
    );

    std::shared_ptr<spdlog::logger> getLogger(const std::string& name);
    void setLevel(const std::string& name, spdlog::level::level_enum level);
    void shutdown();

private:
    LoggerManager() = default;
    ~LoggerManager() = default;

    void addZmqSink(const std::string& loggerName);

    std::string logsDir_;
    std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> loggers_;
    std::mutex mutex_;

    zmq::context_t zqmContext_{1};
    std::mutex zmqMutex_;
};