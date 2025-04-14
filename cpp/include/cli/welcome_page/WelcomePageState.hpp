#pragma once

#include "IWelcomePageState.hpp"

class WelcomePageState: public IWelcomePageState {
public:
    void help() override;
    void exit() override;

    void startSession() override;
    void signUp() override;
};