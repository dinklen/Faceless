#pragma once

#include "../IState.hpp"

// Interface of chat state
class IChatState: public IState {
public:
    virtual void textMessage();
};