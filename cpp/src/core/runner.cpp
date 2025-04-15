#include "runner.hpp"
#include "../../include/cli/StateContext.hpp"

Application::Application() {
    spdlog::info("Runner initialized");
}

void Application::initialize() {
    StateContext* cliContext = new StateContext();

    spdlog::info("initialize application subsystems");
}