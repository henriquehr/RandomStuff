#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <memory>

#define SDL_MAIN_HANDLED // ...
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include "Engine.h"
#include "Logging.h"

class MainWindow {
private:
    SDL_Window *sdl_window_ptr;
    std::unique_ptr<Engine> engine_ptr;
    std::string title;
    int width;
    int height;
    int display_width;
    int display_height;
    int pos_x;
    int pos_y;
    int mouse_pos_x;
    int mouse_pos_y;
    bool full_screen;
    
public:
    MainWindow();
    ~MainWindow();

    void open(std::string title, int width, int height, 
      int starting_pos_x=SDL_WINDOWPOS_CENTERED, 
      int starting_pos_y=SDL_WINDOWPOS_CENTERED, bool full_screen=false);

private:
    void loop();
    void pullWindowEvents();
    void windowEvents(Uint8 event);
    void showFPSInWindowTitle(float fps, float time);
    void setWindowTitle(std::string title);
    void setDisplaySize(int display_width, int display_height);
    void setSize(int width, int height);
    void setPos(int pos_x, int pos_y);
    void setFullScreen(bool full_screen);
};
#endif // !MAINWINDOW_H