#ifndef RENDERABLE_2D_H
#define RENDERABLE_2D_H

#include <memory>
#include <vector>

#include "Shader.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Math/Math.h"
#include "Renderer2D.h"
#include "Texture.h"

struct VertexData {
    Vector3 vertex;
    Vector2 uv;
    float tid;
    unsigned int _color;
};

class Renderable2D {
protected:  
    Vector3 position;
    Vector2 size;
    unsigned int color;
    std::vector<Vector2> UV;
    std::shared_ptr<Texture> texture;

protected:
    Renderable2D();

public:
    Renderable2D(Vector3 position, Vector2 size, unsigned int color);
    virtual ~Renderable2D();

    virtual void submit(std::shared_ptr<Renderer2D> renderer) const;

    void setColor(unsigned int color);
    void setColor(const Vector4 &color);

    inline const Vector2& getSize() const { return this->size; }
    inline const Vector3& getPosition() const { return this->position; }
    inline unsigned int getColor() const { return this->color; }
    inline const std::vector<Vector2>& getUV() const { return this->UV; }
    inline const GLuint getTID() const { 
        return texture ? texture->getID() : 0;
    }

private:
    inline void setUVDefaults();
};
#endif // !RENDERABLE_2D_H