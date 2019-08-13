#include "MainWindow.h"

MainWindow::MainWindow() 
  : sdl_window_ptr(nullptr), title(""), width(0), height(0), display_width(0), 
  display_height(0), pos_x(0), pos_y(0), mouse_pos_x(0), mouse_pos_y(0), full_screen(false) {

    LOG(MESSAGE) << "======================== WELCOME TO THE MIND BENDING ENGINE ========================";
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG(ERROR) << "SDL initialization failed.";
    }
    LOG(MESSAGE) << "SDL initialized.";
}

MainWindow::~MainWindow() {
    SDL_DestroyWindow(this->sdl_window_ptr);
    SDL_Quit();
    this->engine_ptr = nullptr;
    LOG(MESSAGE) << "Main window closed.";
    LOG(MESSAGE) << "======================== GOOD BYE ========================";
}

void MainWindow::open(std::string title, int width, int height, 
  int starting_pos_x, int starting_pos_y, bool full_screen) {

    if (this->sdl_window_ptr != nullptr) {
        LOG(WARNING) << "Window is already open.";
        return;
    }
    SDL_DisplayMode display;
    SDL_GetCurrentDisplayMode(0, &display);
    this->sdl_window_ptr = SDL_CreateWindow(title.c_str(), starting_pos_x, 
      starting_pos_y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (this->sdl_window_ptr == nullptr) {
        LOG(ERROR) << "Main window creation failed.";
    }
    if (SDL_GL_CreateContext(this->sdl_window_ptr) == NULL) {
        LOG(ERROR) << "Context initialization failed.";
    }
    //SDL_GL_MakeCurrent(_window, glContext);
    //SDL_WarpMouseGlobal(display.w / 2, display.h / 2);
    SDL_GL_SetSwapInterval(0);
    this->setWindowTitle(title);
    this->setDisplaySize(display.w, display.h);
    this->setSize(width, height);
    this->setPos(starting_pos_x, starting_pos_y);
    this->setFullScreen(full_screen);
    LOG(MESSAGE) << "Main window opened.";
    this->engine_ptr = std::make_unique<Engine>();
    this->engine_ptr->init();
    this->loop();
}

void MainWindow::loop() {
    this->engine_ptr->start();
    while (this->engine_ptr->status != Engine::STATUS::STOPPED) {
        this->pullWindowEvents();
        this->engine_ptr->loop();
        SDL_GL_SwapWindow(this->sdl_window_ptr);
// #if (showLoopTime)
        // if (this->engine_ptr->loop_time >= 1000.0f) {
        //     showFPSInWindowTitle(this->engine_ptr->frame_count, this->engine_ptr->last_time);
        // }
// #endif
    }
    LOG(MESSAGE) << "Loop ended.";
}

// SDL events
void MainWindow::pullWindowEvents() {
    SDL_GetMouseState(&mouse_pos_x, &mouse_pos_y);
    this->engine_ptr->getInputPTR()->updateMousePos(mouse_pos_x, mouse_pos_y);
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            this->engine_ptr->stop();
            break;
        case SDL_KEYDOWN:
            this->engine_ptr->getInputPTR()->sendKeyDownName(
              SDL_GetKeyName(event.key.keysym.sym));
            
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                this->engine_ptr->stop();
            }
            this->engine_ptr->getInputPTR()->sendKeyUpName(
              SDL_GetKeyName(event.key.keysym.sym));
            
            break;
        case SDL_MOUSEBUTTONDOWN:
            this->engine_ptr->getInputPTR()->sendMouseButtonDownID(
              event.button.button, event.button.x, event.button.y);
            
            break;
        case SDL_MOUSEBUTTONUP:
            this->engine_ptr->getInputPTR()->sendMouseButtonUpID(
              event.button.button, event.button.x, event.button.y);
            
            break;
        case SDL_WINDOWEVENT:
            this->windowEvents(event.window.event);
            break;
        default:
            break;
        }
    }
}

// SDL window events
void MainWindow::windowEvents(Uint8 event) {
    switch (event) {
    case SDL_WINDOWEVENT_SHOWN:
        SDL_GetWindowSize(this->sdl_window_ptr, &this->width, &this->height);
        this->engine_ptr->resizeViewport(this->width, this->height);
        LOG(MESSAGE) << "Window shown.";
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        LOG(MESSAGE) << "Window hidden.";
        break;
    case SDL_WINDOWEVENT_EXPOSED:
        LOG(MESSAGE) << "Window exposed.";
        break;
    case SDL_WINDOWEVENT_MOVED:
        LOG(MESSAGE) << "Window moved.";
        break;
    case SDL_WINDOWEVENT_RESIZED:
        SDL_GetWindowSize(this->sdl_window_ptr, &this->width, &this->height);
        this->engine_ptr->resizeViewport(this->width, this->height);
        LOG(MESSAGE) << "Window resized.";
        break;
    case SDL_WINDOWEVENT_SIZE_CHANGED:
        LOG(MESSAGE) << "Window size changed.";
        break;
    case SDL_WINDOWEVENT_MINIMIZED:
        LOG(MESSAGE) << "Window minimized.";
        this->engine_ptr->pause();
        break;
    case SDL_WINDOWEVENT_MAXIMIZED:
        LOG(MESSAGE) << "Window maximized.";
        break;
    case SDL_WINDOWEVENT_RESTORED:
        LOG(MESSAGE) << "Window restored.";
        this->engine_ptr->resume();
        break;
    case SDL_WINDOWEVENT_ENTER:
        LOG(MESSAGE) << "Mouse entered window.";
        break;
    case SDL_WINDOWEVENT_LEAVE:
        LOG(MESSAGE) << "Mouse left window.";
        break;
    case SDL_WINDOWEVENT_FOCUS_GAINED:
        LOG(MESSAGE) << "Window gained keyboard focus.";
        break;
    case SDL_WINDOWEVENT_FOCUS_LOST:
        LOG(MESSAGE) << "Window lost keyboard focus.";
        break;
    case SDL_WINDOWEVENT_CLOSE:
        LOG(MESSAGE) << "Window closed.";
        break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
    case SDL_WINDOWEVENT_TAKE_FOCUS:
        LOG(MESSAGE) << "Window is offered a focus.";
        break;
    case SDL_WINDOWEVENT_HIT_TEST:
        LOG(MESSAGE) << "Window has a special hit test.";
        break;
#endif
    default:
        LOG(MESSAGE) << "Window got unknown event.";
        break;
    }
}

void MainWindow::showFPSInWindowTitle(float fps, float time) {
    std::ostringstream ss;
    ss << "FPS: " << fps;
    ss << " - LOOP TIME: " << time << "ms";
    this->setWindowTitle(ss.str());
}

void MainWindow::setWindowTitle(std::string title) {
    this->title = title;
    SDL_SetWindowTitle(this->sdl_window_ptr, title.c_str());
    LOG(MESSAGE) << "Main window renamed.";
}

void MainWindow::setDisplaySize(int display_width, int display_height) {
    this->display_width = display_width;
    this->display_height = display_height;
    // TODO add SDL stuff and graphics stuff 
    LOG(MESSAGE) << "Display resized.";
}

void MainWindow::setSize(int width, int height) {
    this->width = width;
    this->height = height;
    SDL_SetWindowSize(this->sdl_window_ptr, width, height);
    LOG(MESSAGE) << "Main window resized.";
}

void MainWindow::setPos(int pos_x, int pos_y) {
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    SDL_SetWindowPosition(this->sdl_window_ptr, pos_x, pos_y);
    LOG(MESSAGE) << "Main window moved.";
}

void MainWindow::setFullScreen(bool full_screen) {
    this->full_screen = full_screen;
    if (full_screen) {
        SDL_SetWindowFullscreen(this->sdl_window_ptr, SDL_WINDOW_FULLSCREEN);
        LOG(MESSAGE) << "Window fullscreen set to true.";
    } else {
        // TODO remove from full screen SDL_SetWindowFullscreen(this->sdl_window_ptr, SDL_WINDOW_FULLSCREEN);
        LOG(MESSAGE) << "Window fullscreen set to false.";
    }
}