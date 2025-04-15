#pragma once

#include <memory>

#include <spdlog/spdlog.h>

class Application {
public:
    Application();
    ~Application();

    void initialize();
    void run();
    void shutdown();
}