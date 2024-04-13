//
// Created by Vache Gasparyan on 29.12.23.
//
#pragma once
namespace sdl {

inline std::size_t generateGraphicElementID() {
    static std::size_t id = 0;
    return id++;
}

}  // namespace sdl
