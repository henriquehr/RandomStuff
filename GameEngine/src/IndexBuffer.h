#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/glad.h>

class IndexBuffer {
private:
    GLuint index_buffer_ID;
    GLuint count;

public:
    IndexBuffer(GLushort *data, GLsizei count);
    IndexBuffer(GLuint *data, GLsizei count);
    IndexBuffer() {}
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    GLuint getCount() const;
};
#endif // !INDEX_BUFFER_H