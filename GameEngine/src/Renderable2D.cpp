#include "Renderable2D.h"

Renderable2D::Renderable2D(Vector3 position, Vector2 size, unsigned int color)
: position(position), size(size), color(color), texture(nullptr) {
    this->setUVDefaults();
}

Renderable2D::Renderable2D() : texture(nullptr) {
    this->setUVDefaults();
}

Renderable2D::~Renderable2D() {}

void Renderable2D::submit(std::shared_ptr<Renderer2D> renderer) const {
    renderer->submit(std::make_shared<Renderable2D>(*this));
}

void Renderable2D::setColor(unsigned int color) {
    this->color = color;
}

void Renderable2D::setColor(const Vector4 &color) {
    int r = color.x * 255.0f;
    int g = color.y * 255.0f;
    int b = color.z * 255.0f;
    int a = color.w * 255.0f;
    this->color = a << 24 | b << 16 | g << 8 | r;
}

void Renderable2D::setUVDefaults() {
    this->UV.push_back(Vector2(0, 0));
    this->UV.push_back(Vector2(0, 1));
    this->UV.push_back(Vector2(1, 1));
    this->UV.push_back(Vector2(1, 0));
}
