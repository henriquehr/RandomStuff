#include "Sprite.h"

Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
: Renderable2D(Vector3(x, y, 0), Vector2(width, height), color) {

}

Sprite::Sprite(float x, float y, float width, float height, std::shared_ptr<Texture> texture) 
  : Renderable2D(Vector3(x, y, 0), Vector2(width, height), 0xffffffff) {

      this->texture = texture;
}


Sprite::~Sprite() {}