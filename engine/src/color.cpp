#include "color.hpp"

namespace sdl {

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    : _r{r}, _g{g}, _b{b}, _a{a} {}
unsigned char Color::r() const { return _r; }

unsigned char Color::g() const { return _g; }

unsigned char Color::b() const { return _b; }

unsigned char Color::a() const { return _a; }

} // namespace sdl