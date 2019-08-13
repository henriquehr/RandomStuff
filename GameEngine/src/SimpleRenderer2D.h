#ifndef SIMPLE_RENDERER_2D_H
#define SIMPLE_RENDERER_2D_H

#include <deque>

#include "Renderer2D.h"
#include "StaticSprite.h"

class SimpleRenderer2D : public Renderer2D {
private:
    std::deque<std::shared_ptr<StaticSprite>> render_queue;

public:
    SimpleRenderer2D();
    ~SimpleRenderer2D();

    void submit(std::shared_ptr<Renderable2D> renderable) override;
    void flush() override;
};
#endif // !SIMPLE_RENDERER_2D_H