#pragma once

#include "IWelcomePageState.hpp"

// Welcome page state
class WelcomePageState: public IWelcomePageState {
public:
    void help() override;
    void exit() override;

    void startSession() override;
    void signUp() override;
};