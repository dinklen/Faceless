#pragma once

#include "../IState.hpp"

// Interface of welcome page state
class IWelcomePageState: public IState {
public:
    virtual void startSession();
    virtual void signUp();
};