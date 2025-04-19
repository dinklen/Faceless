#include "../../include/logging/LoggerManager.hpp"
#include "../../include/logging/ZmqSink.hpp"

// Logger manager methods
LoggerManager& LoggerManager::instance() {
    static LoggerManager instance;
    return instance;
}

void LoggerManager::initialize(
    const std::string& defaultLogsDir = "../../logs",
    spdlog::level::level_enum defaultLevel = spdlog::level::info
) {
    logsDir_ = defaultLogsDir;

    spdlog::init_thread_pool(8192, 1);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] %v");

    createLogger("default", defaultLevel);
}

std::shared_ptr<spdlog::logger> LoggerManager::createLogger(
    const std::string& name,
    spdlog::level::level_enum level = spdlog::level::info,
    size_t maxFileSize = 1024 * 1024 * 10,
    size_t maxFiles = 5
) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (auto it = loggers_.find(name); it != loggers_.end()) {
        return it->second;
    }

    try {
        auto sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logsDir_ + "/" + name + ".log", maxFileSize, maxFiles);

        auto logger = std::make_shared<spdlog::async_logger>(name, sink, spdlog::thread_pool());

        logger->set_level(level);
        loggers_[name] = logger;
        spdlog::register_logger(logger);
        addZmqSink(name);
        return logger;
    } catch (const spdlog::spdlog_ex& ex) {
        spdlog::get("default")->error("Failed to create logger '{}': {}", name, ex.what());
        return spdlog::get("default");
    }
}

std::shared_ptr<spdlog::logger> LoggerManager::getLogger(const std::string& name) {
    std::lock_guard<std::mutex> lock(mutex_);

    if (auto it = loggers_.find(name); it != loggers_.end()) {
        return it->second;
    }

    spdlog::get("default")->warn("Logger '{}' not found, usind default", name);
    return spdlog::get("default");
}

void LoggerManager::setLevel(const std::string& name, spdlog::level::level_enum level) {
    if (auto logger = LoggerManager::getLogger(name)) {
        logger->set_level(level);
    }
}

void LoggerManager::shutdown() {
    std::lock_guard<std::mutex> lock(mutex_);
    spdlog::shutdown();
    loggers_.clear();
}

void LoggerManager::addZmqSink(const std::string& loggerName) {
    std::lock_guard<std::mutex> lock(zmqMutex_);

    if (auto logger = spdlog::get(loggerName)) {
        zmq::socket_t zmqSocket(zmqContext_, ZMQ_PUSH);
        zmqSocket.connect("tcp://localhost:45875");

        auto zmqSink = std::make_shared<ZmqSink<std::mutex>>(std::move(zmqSocket));
        logger->sinks().push_back(zmqSink);
    }
}