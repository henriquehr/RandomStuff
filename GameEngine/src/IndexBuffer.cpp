#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(GLushort *data, GLsizei count)
: count(count) {
    glGenBuffers(1, &this->index_buffer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::IndexBuffer(GLuint *data, GLsizei count)
: count(count){
    glGenBuffers(1, &this->index_buffer_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &this->index_buffer_ID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_ID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint IndexBuffer::getCount() const {
    return this->count;
}
