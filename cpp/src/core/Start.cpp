#include "Start.hpp"

#include <atomic>
#include <signal>

struct ApplicationStarter::Impl {
    std::atomic<bool> running{false};
    InitCallback initCallback;
    RunCallback runCallback;
    ShutdownCallback shutdownCallback;
    std::shared_ptr<spdlog::logger> logger;
};

ApplicationStarter::ApplicationStarter(): pimpl(new Impl) {
    // Signal initialization
    signal(SIGINT, [](int){ApplicationStarter::instance().stop();});
    signal(SIGTERM, [](int){ApplicationStarter::instance().stop();});
}

ApplicationStarter::~ApplicationStarter() = default;

void ApplicationStarter::initializeCore() {
    LoggerManager::instance().initialuze();
    pimpl->logger = LoggerManager::instance().getLogger("default");
    pimpl->logger->info("Core initialized");
}

void ApplicationStarter::initializeComponents() {
    if (pimpl->initCallback) {
        pimpl->initCallback();
        pimpl->logger->info("Components initialized");
    }
}

void Application::start() {
    try {
        initializeCore();
        initializeComponents();

        pimpl->running = true;
        pimpl->logger->info("Application started");

        if (pimpl->runCallback) {
            while (pimpl->running) {
                pimpl->runCallback();
            }
        }
    } catch (const std::exception& e) {
        pimpl->logger->critical("Startup failed: {}", e.what());
        shutdownComponents();
    }
}

void Application::stop() {
    pimpl->running = false;
    pimpl->logger->info("Shutting down...");

    if (pimpl->shutdownCallback) {
        pimpl->shutdownCallback();
    }
    shutdownComponents();
}

void Application::setInitCallback(InitCallback callback) {
    pimpl->initCallback = std::move(callback);
}

void Application::setRunCallback(RunCallback callback) {
    pimpl->runCallback = std::move(callback);
}

void Application::setShutdownCallback(ShutdownCallback callback) {
    pimpl->shutdownCallback = std::move(callback);
}

bool Application::isRunning() const {
    return pimpl->running;
}