#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "Utils.h"

class Texture {
private:
    const char *file_name;
    GLuint TID;
    GLsizei width;
    GLsizei height;

public:
    Texture(const char *file_name);
    ~Texture();

    void bind() const;
    void unbind() const;

    inline const unsigned int getID() const { return this->TID; }
    inline const unsigned int getWidth() const {
        return this->width;
    }
    inline const unsigned int getHeight() const {
        return this->height;
    }

private:
    inline GLuint load();
};
#endif // !TEXTURE_H