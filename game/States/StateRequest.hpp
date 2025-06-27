#pragma once
#include <memory>
#include <vector>
#include <variant>
//#include "GameState.hpp"
//#include "StateManager.hpp"

// Declaración adelantada para romper dependencia circular
class GameState;
class StateManager;

// Tipos de solicitudes
struct RequestPushState {
    std::unique_ptr<GameState> state;
};

struct RequestPopState {};
struct RequestChangeState {
    std::unique_ptr<GameState> state;
};
struct RequestQuit {};

using StateRequest = std::variant<
    RequestPushState,
    RequestPopState,
    RequestChangeState,
    RequestQuit
>;

class StateRequestHandler {
public:
    void handleRequest(StateRequest request);
    void applyRequests(StateManager& manager);
    
private:
    std::vector<StateRequest> pendingRequests;
};