#ifndef INPUT_H
#define INPUT_H

#include "Logging.h"

class Input {
private:
    enum M_BUTTON{
        L_BUTTON=1,
        R_BUTTON=3
    };

public:
    int mouse_pos_x;
    int mouse_pos_y;

public:
    Input();
    ~Input();

    void updateMousePos(int x, int y);
    void sendKeyDownName(const char *name);
    void sendKeyUpName(const char *name);
    void sendMouseButtonDownID(int id, int x, int y);
    void sendMouseButtonUpID(int id, int x, int y);
    void mousePos(int *x, int *y);
};

#endif // !INPUT_H