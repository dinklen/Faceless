#pragma once

#include "IState.hpp"

#include <memory>

// State context
class StateContext {
public:
    StateContext();

    void setState(std::uninque_ptr<IState> newState);

public:
    std::unique_ptr<IState> state;
};