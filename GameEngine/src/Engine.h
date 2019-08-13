#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <vector>

#include "GraphicsAPI.h"
#include "Timer.h"
#include "Logging.h"
#include "Input.h"

#define showLoopTime 1

class Engine {
public:
    enum STATUS {
        NOT_INITIALIZED,
        INITIALIZED,
        RUNNING,
        STOPPED,
        PAUSED
    };

private:
    std::shared_ptr<GraphicsAPI> graphics_api_ptr;
    std::shared_ptr<Timer> timer_ptr;
    std::shared_ptr<Input> input_ptr;

public:
    Engine::STATUS status;

public:
    Engine();
    ~Engine();

    void init();
    void loop();
    void update();
    void render();
    void start();
    void resume();
    void pause();
    void paused();
    void stop();
    void resizeViewport(int w, int h);
    std::shared_ptr<Input> getInputPTR(); // TODO change this   

private:
    void computeLoopTime();
};
#endif // !ENGINE_H