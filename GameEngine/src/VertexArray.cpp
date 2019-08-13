#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &this->vertex_array_ID);
}

VertexArray::~VertexArray() {
    // for (int i = 0; i < this->buffers.size(); i++) {
    //     delete buffers[i];
    // }
    this->buffers.clear();
    glDeleteBuffers(1, &this->vertex_array_ID);
}

void VertexArray::addBuffer(std::shared_ptr<Buffer> buffer, GLuint index) {
    this->bind();
    buffer->bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
    buffer->unbind();
    this->unbind();
    this->buffers.push_back(buffer);
}

void VertexArray::bind() const {
    glBindVertexArray(this->vertex_array_ID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}