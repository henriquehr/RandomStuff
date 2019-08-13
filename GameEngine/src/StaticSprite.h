#ifndef STATIC_SPRITE_H
#define STATIC_SPRITE_H

#include <memory>

#include "Renderable2D.h"
#include "Math/Math.h"

class StaticSprite : public Renderable2D {
private:
    std::shared_ptr<VertexArray> vertex_array;
    std::shared_ptr<IndexBuffer> index_buffer;
    std::shared_ptr<Shader> shader;

public:
    StaticSprite(float x, float y, float width, float height, const Vector4 &color, std::shared_ptr<Shader> shader);
    ~StaticSprite();

    inline const std::shared_ptr<VertexArray> getVAO() const { return vertex_array; }
    inline const std::shared_ptr<IndexBuffer> getIBO() const { return index_buffer; }
    inline std::shared_ptr<Shader> getShader() const { return shader; }
};
#endif // !STATIC_SPRITE_H