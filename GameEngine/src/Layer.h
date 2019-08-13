#ifndef LAYER_H
#define LAYER_H

#include <memory>
#include "Renderable2D.h"
#include "Renderer2D.h"
#include "Shader.h"
#include "Math/Math.h"

class Layer {
protected:
    std::shared_ptr<Renderer2D> renderer;
    std::vector<std::shared_ptr<Renderable2D>> renderables;
    std::shared_ptr<Shader> shader;
    Matrix4 projection_matrix;

public:
    virtual ~Layer();
    
    virtual void add(std::shared_ptr<Renderable2D> renderable);
    virtual void render();
    inline const std::vector<std::shared_ptr<Renderable2D>> getRenderables() const {
        return this->renderables;
    }

protected:
    Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, 
      Matrix4 projection_matrix);
};
#endif // !LAYER_H