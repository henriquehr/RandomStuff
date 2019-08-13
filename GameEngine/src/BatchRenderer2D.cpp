#include "BatchRenderer2D.h"

BatchRenderer2D::BatchRenderer2D() {
    this->init();
    LOG(MESSAGE) << "Using BatchRenderer2D";
}

BatchRenderer2D::~BatchRenderer2D() {
    // delete this->IBO;
    glDeleteBuffers(1, &this->VBO);
}

void BatchRenderer2D::init() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
    glEnableVertexAttribArray(SHADER_UV_INDEX);
    glEnableVertexAttribArray(SHADER_TID_INDEX);
    glEnableVertexAttribArray(SHADER_COLOR_INDEX);
    glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 
      RENDERER_VERTEX_SIZE, (const GLvoid*) 0);

    glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, 
      RENDERER_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, uv));

    glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, 
      RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));

    glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, 
      RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, _color)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLuint *indices = new GLuint[RENDERER_INDICES_SIZE];
    int offset = 0;
    for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;
        offset += 4;
    }
    this->IBO = std::make_unique<IndexBuffer>(indices, RENDERER_INDICES_SIZE);
    glBindVertexArray(0);
    delete[] indices;
}

void BatchRenderer2D::begin() {
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    this->buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

}

void BatchRenderer2D::submit(std::shared_ptr<Renderable2D> renderable) {
        const Vector3 &position = renderable->getPosition();
        const Vector2 &size = renderable->getSize();
        const unsigned int color = renderable->getColor();
        const std::vector<Vector2> &uv = renderable->getUV();
        const GLuint tid = renderable->getTID();
        float ts = 0.0f;
        if (tid > 0) {
            bool found = false;
            for (int i = 0; i < this->texture_slots.size(); i++) {
                if (this->texture_slots[i] == tid) {
                    ts = (float)(i + 1);
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (this->texture_slots.size() >= 32) {
                    end();
                    flush();
                    begin();
                }
                this->texture_slots.push_back(tid);
                ts = (float)(this->texture_slots.size());
            }
        }
        
        this->buffer->vertex = *transformation_back * position;
        this->buffer->uv = uv[0];
        this->buffer->tid = ts;
        this->buffer->_color = color;
        this->buffer++;
        this->buffer->vertex = *transformation_back * 
          Vector3(position.x, position.y + size.y, position.z);

        this->buffer->uv = uv[1];
        this->buffer->tid = ts;
        this->buffer->_color = color;
        this->buffer++;

        this->buffer->vertex = *transformation_back * 
          Vector3(position.x + size.x, position.y + size.y, position.z);

        this->buffer->uv = uv[2];
        this->buffer->tid = ts;
        this->buffer->_color = color;
        this->buffer++;
        
        this->buffer->vertex = *transformation_back * 
          Vector3(position.x + size.x, position.y, position.z);

        this->buffer->uv = uv[3];
        this->buffer->tid = ts;
        this->buffer->_color = color;
        this->buffer++;
        this->index_count += 6;
}

void BatchRenderer2D::end() {
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchRenderer2D::flush() {
    for (int i = 0; i < this->texture_slots.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, this->texture_slots[i]);
    }
    glBindVertexArray(this->VAO);
    this->IBO->bind();
    glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, NULL);
    this->IBO->unbind();
    glBindVertexArray(0);
    this->index_count = 0;
}

void BatchRenderer2D::drawString(const std::string &text, const 
  Vector3 &position, const std::shared_ptr<Font_> &font, unsigned int color) {

    float ts = 0.0f;
    bool found = false;
    for (int i = 0; i < this->texture_slots.size(); i++) {
        if (this->texture_slots[i] == font->getID()) {
            ts = (float)(i + 1);
            found = true;
            break;
        }
    }
    if (!found) {
        if (this->texture_slots.size() >= 32) {
            end();
            flush();
            begin();
        }
        this->texture_slots.push_back(font->getID());
        ts = (float)(this->texture_slots.size());
    }

    float scaleX = 960.0f / 32.0f;
    float scaleY = 540.0f / 18.0f;
    float x = position.x;

    ftgl::texture_font_t *ft_font = font->getFTFont();
    for (int i = 0; i < text.length(); i++) {
        const unsigned int c = text[i];
        ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(ft_font, c);
        if (glyph != NULL) {

            if (i > 0) {
                float kerning = ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
                x += kerning / scaleX;
            }

            float x0 = x + glyph->offset_x / scaleX;
            float y0 = position.y + glyph->offset_y / scaleY;
            float x1 = x0 + glyph->width / scaleX;
            float y1 = y0 - glyph->height / scaleY;

            float u0 = glyph->s0;
            float v0 = glyph->t0;
            float u1 = glyph->s1;
            float v1 = glyph->t1;

            this->buffer->vertex = *this->transformation_back * Vector3(x0, y0, 0);
            this->buffer->uv = Vector2(u0, v0);
            this->buffer->tid = ts;
            this->buffer->_color = color;
            this->buffer++;

            this->buffer->vertex = *this->transformation_back * Vector3(x0, y1, 0);
            this->buffer->uv = Vector2(u0, v1);
            this->buffer->tid = ts;
            this->buffer->_color = color;
            this->buffer++;

            this->buffer->vertex = *this->transformation_back * Vector3(x1, y1, 0);
            this->buffer->uv = Vector2(u1, v1);
            this->buffer->tid = ts;
            this->buffer->_color = color;
            this->buffer++;

            this->buffer->vertex = *this->transformation_back * Vector3(x1, y0, 0);
            this->buffer->uv = Vector2(u1, v0);
            this->buffer->tid = ts;
            this->buffer->_color = color;
            this->buffer++;

            this->index_count += 6;
            x += glyph->advance_x / scaleX;
        }
    }
}