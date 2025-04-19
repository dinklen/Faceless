#pragma once

#include <memory>
#include <functional>

#include "../../include/logging/LoggerManager.hpp"

class ApplicationStarter {
public:
    using InitCallback = std::function<void()>;
    using RunCallback = std::function<void()>;
    using ShutdownCallback = std::function<void()>;

    ApplicationStarter();
    virtual ~ApplicationStarter();

    // Configuration
    void setInitCallback(InitCallback callback);
    void setRunCallback(RunCallback callback);
    void setShutdownCallback(ShutdownCallback callback);

    // Event loop
    void start();
    void stop();

    // Status
    bool isRunning() const;

protected:
    // virtual void parseArguments(int argc, char* argv[]);
    virtual void initializeCore();
    virtual void initializeComponents();
    virtual void shutdownComponents();

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl;
};