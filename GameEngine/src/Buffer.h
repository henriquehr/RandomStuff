#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

class Buffer {
private:
    GLuint buffer_ID;
    GLuint component_count;

public:
    Buffer(GLfloat *data, GLsizei count, GLuint component_count);
    ~Buffer();

    void bind() const;
    void unbind() const;
    GLuint getComponentCount() const;
};
#endif // !BUFFER_H