#pragma once

#include "IAccountState.hpp"

// Account state
class AccountState: public IAccountState {
public:
    void help() override;
    void exit() override;

    void open() override;
    void del() override;
    void rename() override;
    void select() override;
    void deselect() override;
};