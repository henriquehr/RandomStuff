#include <memory>
#include <string>

#include "MainWindow.h"

// TODO commenting comes later, things will change

int main(int argc, char** argv) {
    int width = 960;
    int height = 540;
    std::string title = "Mind Bending Engine";
    std::unique_ptr<MainWindow> window = std::make_unique<MainWindow>();
    window->open(title, width, height);
    return 0;
}
