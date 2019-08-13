#include "Texture.h"

Texture::Texture(const char *file_name) 
  : file_name(file_name) {
      this->TID = this->load();
}

Texture::~Texture() {}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->TID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::load() {
    BYTE *pixels = Utils::loadImage(this->file_name, &this->width, &this->height);
    GLuint result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_BGR,
      GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    delete[] pixels;
    return result;
}
