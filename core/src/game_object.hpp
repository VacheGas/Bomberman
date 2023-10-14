#pragma once

#include "sprite.hpp"

using namespace std;

class GameObject {
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
    virtual void load(const Sprite& params) = 0;

protected:
    GameObject() {}
    virtual ~GameObject() {}
};
