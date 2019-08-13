#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <memory>
#include <vector>
#include <glad/glad.h>

#include "Buffer.h"

class VertexArray {
private:
    GLuint vertex_array_ID;
    std::vector<std::shared_ptr<Buffer>> buffers;

public:
    VertexArray();
    ~VertexArray();

    void addBuffer(std::shared_ptr<Buffer> buffer, GLuint index);
    void bind() const;
    void unbind() const;
};
#endif // !VERTEX_ARRAY_H