#include "StateRequest.hpp"
#include "StateManager.hpp"

void StateRequestHandler::handleRequest(StateRequest request) {
    pendingRequests.push_back(std::move(request));
}

void StateRequestHandler::applyRequests(StateManager& manager) {
    for (auto& request : pendingRequests) {
        std::visit([&manager](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            
            if constexpr (std::is_same_v<T, RequestPushState>) {
                manager.pushState(std::move(arg.state));
            }
            else if constexpr (std::is_same_v<T, RequestPopState>) {
                manager.popState();
            }
            else if constexpr (std::is_same_v<T, RequestChangeState>) {
                manager.changeState(std::move(arg.state));
            }
        }, request);
    }
    pendingRequests.clear();
}

