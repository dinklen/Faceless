#pragma once

#include "IChatState.hpp"

// Chat state
class ChatState: public IChatState {
    void help() override;
    void exit() override;

    void textMessage() override;
};