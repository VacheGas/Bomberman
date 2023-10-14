#include "exception.hpp"

namespace sdl {

SDLException::SDLException(const std::string &message)
    : std::runtime_error(message) {}

const char *SDLException::what() const noexcept {
  return std::runtime_error::what();
}

} // namespace sdl