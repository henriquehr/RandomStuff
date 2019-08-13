#ifndef GROUP_H
#define GROUP_H

#include "Renderable2D.h"

class Group : public Renderable2D {
private:
    std::vector<std::shared_ptr<Renderable2D>> renderables;
    Matrix4 transformation_matrix;

public:
    Group(const Matrix4 &transform);
    ~Group();

    void add(std::shared_ptr<Renderable2D> renderable);
    void submit(std::shared_ptr<Renderer2D> renderer) const override;
};
#endif // !GROUP_H