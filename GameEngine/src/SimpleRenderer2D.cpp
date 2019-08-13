#include "SimpleRenderer2D.h"

SimpleRenderer2D::SimpleRenderer2D() {
    LOG(MESSAGE) << "Using SimpleRenderer2D";
}

SimpleRenderer2D::~SimpleRenderer2D() {

}

void SimpleRenderer2D::submit(std::shared_ptr<Renderable2D> renderable) {
    this->render_queue.push_back(std::dynamic_pointer_cast<StaticSprite>(renderable));
}

void SimpleRenderer2D::flush() {
    while (!this->render_queue.empty()) {
        const std::shared_ptr<StaticSprite> sprite = this->render_queue.front();
        sprite->getVAO()->bind();
        sprite->getIBO()->bind();
        sprite->getShader()->setUniformM4("ml_matrix", Matrix4::createTranslation(sprite->getPosition()));
        glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);
        sprite->getIBO()->unbind();
        sprite->getVAO()->unbind();
        this->render_queue.pop_front();
    }
}