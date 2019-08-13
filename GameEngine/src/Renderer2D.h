#ifndef RENDERER_2D
#define RENDERER_2D

#include <vector>
#include <memory>

#include <glad/glad.h>

#include "Math/Math.h"
#include "Font.h"

class Renderable2D;

class Renderer2D {
protected:
    std::vector<Matrix4> transformation_stack;
    const Matrix4* transformation_back;

protected:
    Renderer2D() {
        this->transformation_stack.push_back(Matrix4::createIdentity());
        this->transformation_back = &this->transformation_stack.back();
    }

    virtual ~Renderer2D() {}

public:
    void push(const Matrix4 &matrix, bool override=false) {
        if (override){
            this->transformation_stack.push_back(matrix);
        } else {
            this->transformation_stack.push_back(this->transformation_stack.back() 
              * matrix);
        }
        this->transformation_back = &this->transformation_stack.back();
    }

    void pop() {
        if (this->transformation_stack.size() > 1) {
            this->transformation_stack.pop_back();
        }
        this->transformation_back = &this->transformation_stack.back();
    }

    virtual void begin() {};
    virtual void submit(std::shared_ptr<Renderable2D> renderable) = 0;
    virtual void drawString(const std::string &text, const Vector3 &position,
      const std::shared_ptr<Font_> &font, unsigned int color) {}
    virtual void end() {};
    virtual void flush() = 0;
};
#endif // !RENDERER_2D