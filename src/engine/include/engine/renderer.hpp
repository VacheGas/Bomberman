//
// Created by Vache Gasparyan on 24.12.23.
//

#ifndef BOMBERMAN_RENDERER_HPP
#define BOMBERMAN_RENDERER_HPP
#include <SDL3/SDL.h>

#include <string>

namespace sdl {

class Renderer {
   public:
    Renderer() = default;
    Renderer(int flag, std::size_t width, std::size_t height, std::string title);

   public:


   private:
    int _flags{};
    std::size_t _width{};
    std::size_t _height{};
    SDL_Renderer* _renderer{};
    SDL_Window* _window;
    std::string _title;
};

}  // namespace sdl

#endif  //BOMBERMAN_RENDERER_HPP
