//
// Created by Vache Gasparyan on 10.05.24.
//

#include <utility>

#include <components/input_handler_publisher.hpp>
#include <engine/input_handler.hpp>

namespace {
enum class HasActiveSubscribers : bool { TRUE = true, FALSE = false };
struct EventAction {
    std::function<void()> _action;
    bool _isActive;
};
std::array<std::pair<std::vector<EventAction>, HasActiveSubscribers>,
           static_cast<std::size_t>(sdl::ENGINE_SCANCODES::COUNT)>
    keyEventSubscribers;
sdl::InputHandler handler;
}  // namespace

components::SubscriptionID::SubscriptionID(std::size_t index,
                                           sdl::ENGINE_SCANCODES code)
    : _index(index), _subscriptCode(code) {
    keyEventSubscribers[static_cast<std::size_t>(_subscriptCode)]
        .first[_index]
        ._isActive = true;
}

namespace components::InputHandlerPublisher {

std::unique_ptr<components::SubscriptionID, components::SubscriptionIDDeleter>
subscribe(sdl::ENGINE_SCANCODES code, std::function<void()>&& pred) {
    keyEventSubscribers[static_cast<std::size_t>(code)].first.push_back(
        {._action = std::move(pred), ._isActive = true});
    keyEventSubscribers[static_cast<std::size_t>(code)].second =
        HasActiveSubscribers::TRUE;

    return std::unique_ptr<components::SubscriptionID,
                           components::SubscriptionIDDeleter>(
        new components::SubscriptionID(
            keyEventSubscribers[static_cast<std::size_t>(code)].first.size() -
                1,
            code));
}

void monitoringInputHandler() {
    constexpr sdl::ScancodesEngine scancodesEngine =
        sdl::InputHandler::supportedEngineScancodes();
    handler.update();
    for (auto item : scancodesEngine) {
        if (handler.isKeyPressed(item)) {
            if (keyEventSubscribers[static_cast<std::size_t>(item)].second ==
                HasActiveSubscribers::TRUE) {
                keyEventSubscribers[static_cast<std::size_t>(item)].second =
                    HasActiveSubscribers::FALSE;
                for (const auto& function :
                     keyEventSubscribers[static_cast<std::size_t>(item)]
                         .first) {
                    if (function._isActive) {
                        function._action();
                        keyEventSubscribers[static_cast<std::size_t>(item)]
                            .second = HasActiveSubscribers::TRUE;
                    }
                }
            }
        }
    }
}
}  // namespace components::InputHandlerPublisher

void components::SubscriptionIDDeleter::operator()(
    components::SubscriptionID* subscriptionId) {
    keyEventSubscribers[static_cast<std::size_t>(
                            subscriptionId->_subscriptCode)]
        .first[subscriptionId->_index]
        ._isActive = false;
    delete subscriptionId;
}

// sdl
