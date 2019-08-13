#include "Layer.h"

Layer::Layer(std::shared_ptr<Renderer2D> renderer, std::shared_ptr<Shader> shader, 
  Matrix4 projection_matrix) 
  : renderer(renderer),  shader(shader), projection_matrix(projection_matrix) {

    this->shader->enable();
    this->shader->setUniformM4("pr_matrix", this->projection_matrix);
    this->shader->disable();
}

Layer::~Layer() {
    // delete this->shader;
    // delete this->renderer;
    // for (int i = 0; i < this->renderables.size(); i++) {
    //     delete this->renderables[i];
    // }
    this->renderables.clear();
}

void Layer::add(std::shared_ptr<Renderable2D> renderable) {
    this->renderables.push_back(renderable);
}

void Layer::render() {
    this->shader->enable();
    this->renderer->begin();
    for (int i = 0; i < this->renderables.size(); i++) {
        this->renderables[i]->submit(this->renderer);
    }
    this->renderer->end();
    this->renderer->flush();
}