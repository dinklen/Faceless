#pragma once

class IAccountState: public IState {
public:
    virtual void open();
    virtual void del();
    virtual void rename();
    virtual void select();
    virtual void deselect();
};