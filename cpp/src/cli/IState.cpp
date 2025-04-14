#include "../../include/cli/IState.hpp"

IState::IState(const std::string& name): name(name) {}

std::string IState::getName() const {
    return name;
}