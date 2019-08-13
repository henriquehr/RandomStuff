#ifndef SPRITE_H
#define SPRITE_H

#include <memory>

#include "Renderable2D.h"
#include "Math/Math.h"

class Sprite : public Renderable2D {
public:
    Sprite(float x, float y, float width, float height, unsigned int color);
    Sprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture);
    ~Sprite();
};
#endif // !SPRITE_H