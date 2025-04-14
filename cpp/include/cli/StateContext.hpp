#pragma once

#include "IState.hpp"

#include <memory>

class StateContext {
public:
    StateContext(std::unique_ptr<IState>& state);

    void setState(std::uninque_ptr<IState>& newState);

private:
    std::unique_ptr<IState> state_;
};