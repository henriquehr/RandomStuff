#include "StaticSprite.h"

StaticSprite::StaticSprite(float x, float y, float width, float height, 
  const Vector4 &color, std::shared_ptr<Shader> shader)
  : Renderable2D(Vector3(x, y, 0), Vector2(width, height), 0xffffffff), shader(shader) {
    GLfloat vertices[] = {
        0, 0, 0,
        0, height, 0,
        width, height, 0,
        width, 0, 0
    };
    GLfloat colors[] = {
        color.x, color.y, color.z, color.w,
        color.x, color.y, color.z, color.w,
        color.x, color.y, color.z, color.w,
        color.x, color.y, color.z, color.w
    };
    this->vertex_array = std::make_shared<VertexArray>();
    this->vertex_array->addBuffer(std::make_shared<Buffer>(vertices, 4 * 3, 3), 0);
    this->vertex_array->addBuffer(std::make_shared<Buffer>(colors, 4 * 4, 4), 1);
    GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
    this->index_buffer = std::make_shared<IndexBuffer>(indices, 6);
}

StaticSprite::~StaticSprite() {
    // delete this->vertex_array;
    // delete this->index_buffer;
}