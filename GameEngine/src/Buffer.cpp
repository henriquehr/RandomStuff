#include "Buffer.h"


Buffer::Buffer(GLfloat *data, GLsizei count, GLuint component_count) 
: component_count(component_count) {
    glGenBuffers(1, &this->buffer_ID);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_ID);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &this->buffer_ID);
}

void Buffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_ID);
}

void Buffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint Buffer::getComponentCount() const {
    return this->component_count;
}
