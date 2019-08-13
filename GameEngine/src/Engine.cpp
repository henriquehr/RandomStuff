#include "Engine.h"

Engine::Engine() 
  : status(Engine::STATUS::NOT_INITIALIZED) {}

Engine::~Engine() {
    this->status = Engine::STATUS::NOT_INITIALIZED;
    // delete this->timer_ptr;
    // delete this->input_ptr;
    // delete this->graphics_api_ptr;
}

void Engine::init() {
    if (this->status != Engine::STATUS::NOT_INITIALIZED){
        LOG(WARNING) << "Engine already initialized.";
        return;
    }
    this->timer_ptr = std::make_shared<Timer>();
    this->input_ptr = std::make_shared<Input>();
    this->graphics_api_ptr = std::make_shared<GraphicsAPI>();
    this->graphics_api_ptr->init();
    this->status = Engine::STATUS::INITIALIZED;
}

void Engine::loop() {
    if (this->status == Engine::STATUS::RUNNING) {
        this->graphics_api_ptr->mousePos(this->input_ptr->mouse_pos_x, 
          this->input_ptr->mouse_pos_y);

        this->graphics_api_ptr->updateElapsed(this->timer_ptr->getElapsedTimeStart());
        this->graphics_api_ptr->updateFPS(this->timer_ptr->getFPS());
        this->update();
        this->render();
    } else {
        this->paused();
    }
    this->timer_ptr->computeLoop();
}

void Engine::update() {
    this->graphics_api_ptr->update();
}

void Engine::render() {
    this->graphics_api_ptr->render();

}

void Engine::start() {
    this->status = Engine::STATUS::RUNNING;
    LOG(MESSAGE) << "Engine started.";
}

void Engine::resume() {
    this->status = Engine::STATUS::RUNNING;
    LOG(MESSAGE) << "Engine resumed.";
}

void Engine::pause() {
    LOG(MESSAGE) << "Engine paused.";
    this->status = Engine::STATUS::PAUSED;
}

void Engine::paused() {
    this->timer_ptr->nap(33);
}

void Engine::stop() {
    LOG(MESSAGE) << "Engine stopped.";
    this->status = Engine::STATUS::STOPPED;
}

std::shared_ptr<Input> Engine::getInputPTR() {
    return this->input_ptr;
}

void Engine::resizeViewport(int w, int h) {
    this->graphics_api_ptr->resizeViewport(w, h);
}
