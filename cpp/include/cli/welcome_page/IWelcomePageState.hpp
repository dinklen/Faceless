#pragma once

class IWelcomePageState: public IState {
public:
    virtual void startSession();
    virtual void signUp();
};