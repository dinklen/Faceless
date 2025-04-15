#pragma once

// Interface of account state
class IAccountState: public IState {
public:
    virtual void open();
    virtual void del();
    virtual void rename();
    virtual void select();
    virtual void deselect();
};