#include "../../include/cli/StateContext.hpp"

#include <memory>

StateContext::StateContext() {
    setState(std::make_unique<WelcomePageState>());
}

void StateContext::setState(std::uninque_ptr<IState> newState) {
    state = std::move(newState);
}