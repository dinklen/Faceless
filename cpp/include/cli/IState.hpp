#pragma once

#include <string>

// Basic interface state
class IState {
public:
    virtual ~IState() = default;

    virtual void help() = 0;
    virtual void exit() = 0;
};