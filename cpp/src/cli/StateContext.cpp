#include "../../include/cli/StateContext.hpp"
#include "../../include/cli/IState.hpp"

#include <memory>

StateContext::StateContext(std::unique_ptr<IState>& state): state_(state) {}

void StateContext::setState(std::unique_ptr<IState>& newState) {
    state_ = newState
}
