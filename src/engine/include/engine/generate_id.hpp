//
// Created by Vache Gasparyan on 29.12.23.
//

#ifndef BOMBERMAN_GENERATE_ID_HPP
#define BOMBERMAN_GENERATE_ID_HPP
namespace sdl{

    std::size_t generateGraphicElementID() {
        static std::size_t id = 0;
        return ++id;
    }

}

#endif  //BOMBERMAN_GENERATE_ID_HPP
