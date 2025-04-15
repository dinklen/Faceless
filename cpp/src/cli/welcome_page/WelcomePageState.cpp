#include "../../include/cli/WelcomePageState.hpp"

#include <iostream>

// Help command
void WelcomePageState::help() {
    std::cout << "Commands:\n"
    << "[help] - prints the list of commands\n"
    << "[exit] - closes the application\n"
    << "[sign_up] - registers a new account\n"
    << "[start_session] - starts a new session on this device\n"
    << std::endl;
}

// Exit command
void WelcomePageState::exit() {
    exit(0);
}