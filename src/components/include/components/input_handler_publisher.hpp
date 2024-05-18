//
// Created by Vache Gasparyan on 10.05.24.
//

#ifndef BOMBERMAN_INPUT_HANDLER_PUBLISHER_HPP
#define BOMBERMAN_INPUT_HANDLER_PUBLISHER_HPP

#include <functional>

#include <engine/engine_key_scancodes.hpp>
#include <engine/input_handler.hpp>

namespace components {

class SubscriptionID;

struct SubscriptionIDDeleter {
    void operator()(SubscriptionID* subscriptionId);
};

namespace InputHandlerPublisher {
[[nodiscard]] std::unique_ptr<components::SubscriptionID,
                              components::SubscriptionIDDeleter>
subscribe(sdl::ENGINE_SCANCODES code, std::function<void()>&& pred);
void monitoringInputHandler();
};  // namespace InputHandlerPublisher

class SubscriptionID {
public:
    SubscriptionID() = default;
    SubscriptionID(SubscriptionID&&) = default;
    SubscriptionID& operator=(SubscriptionID&&) = default;

private:
    std::size_t _index;
    sdl::ENGINE_SCANCODES _subscriptCode;

private:
    SubscriptionID(std::size_t id, sdl::ENGINE_SCANCODES code);

    friend std::unique_ptr<components::SubscriptionID,
                           components::SubscriptionIDDeleter>
    InputHandlerPublisher::subscribe(sdl::ENGINE_SCANCODES code,
                                     std::function<void()>&& pred);
    friend struct SubscriptionIDDeleter;
};

}  // namespace components

#endif  //BOMBERMAN_INPUT_HANDLER_PUBLISHER_HPP
