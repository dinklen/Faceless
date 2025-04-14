#pragma once

#include <string>

class IState {
public:
    IState(const std::string& name);

    virtual void help() = 0;
    virtual void exit() = 0;

public:
    std::string name;
};