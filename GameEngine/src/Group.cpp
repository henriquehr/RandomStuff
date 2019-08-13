#include "Group.h"

Group::Group(const Matrix4 &transform) 
  : transformation_matrix(transform) {}

Group::~Group() {
    // for (int i = 0; i < this->renderables.size(); i++) {
    //     delete this->renderables[i];
    // }
    this->renderables.clear();
}

void Group::add(std::shared_ptr<Renderable2D> renderable) {
    this->renderables.push_back(renderable);
}

void Group::submit(std::shared_ptr<Renderer2D> renderer) const {
    renderer->push(this->transformation_matrix);
    for(int i = 0; i < this->renderables.size(); i++) {
        renderables[i]->submit(renderer);
    }
    renderer->pop();
}