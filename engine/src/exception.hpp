#pragma once

#include <stdexcept>
#include <string>

namespace sdl {

class SDLException : public std::runtime_error {
public:
  explicit SDLException(const std::string &message);
  const char *what() const noexcept override;
};

} // namespace sdl