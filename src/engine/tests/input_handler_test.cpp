//
// Created by Vache Gasparyan on 18.02.24.
//
#include "test_utils/gtest_main.hpp"

#include <engine/input_handler.hpp>

class ForCompileTimeTests : public sdl::InputHandler {
public:
    void testSupportedScancodes() {
        static_assert(!sdl::InputHandler::supportedScancodes().empty());
    }

    void testCastEngineScancodesToSdl() {
        static_assert(sdl::InputHandler::castEngineScancodesToSdlScancode(
                          sdl::InputHandler::supportedScancodes(),
                          sdl::ENGINE_SCANCODES::W) == SDL_SCANCODE_W);
    }

    void testCastSdlScancodeToEngineScancode() {
        static_assert(sdl::InputHandler::castSdlScancodeToEngineScancode(
                          sdl::InputHandler::supportedScancodes(),
                          SDL_SCANCODE_W) == sdl::ENGINE_SCANCODES::W);
    }
};

TEST(input_handler, constructor) {
    EXPECT_NO_THROW(sdl::InputHandler());
}

TEST(input_handler, compile_time_code) {
    ForCompileTimeTests obj;
    obj.testSupportedScancodes();
    obj.testCastEngineScancodesToSdl();
    obj.testCastSdlScancodeToEngineScancode();
}
