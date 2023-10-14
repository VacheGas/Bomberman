#pragma once

namespace sdl {

class Color {
public:
  Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  unsigned char r() const;
  unsigned char g() const;
  unsigned char b() const;
  unsigned char a() const;

private:
  unsigned char _r;
  unsigned char _g;
  unsigned char _b;
  unsigned char _a;
};

} // namespace sdl