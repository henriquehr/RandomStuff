#ifndef BATCH_RENDERER_2D_H
#define BATCH_RENDERER_2D_H

#include <cstddef>
#include <memory>
#include <vector>

#include <glad/glad.h>

#include "IndexBuffer.h"
#include "Renderable2D.h"
#include "Renderer2D.h"

#define RENDERER_MAX_SPRITES    60000
#define RENDERER_VERTEX_SIZE    sizeof(VertexData)
#define RENDERER_SPRITE_SIZE    RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE    RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE   RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX     1
#define SHADER_TID_INDEX    2
#define SHADER_COLOR_INDEX  3

class BatchRenderer2D : public Renderer2D {
private:
    GLuint VAO;
    GLuint VBO;
    std::unique_ptr<IndexBuffer> IBO;
    GLsizei index_count;
    VertexData *buffer;
    std::vector<GLuint> texture_slots;

public:
    BatchRenderer2D();
    ~BatchRenderer2D();

    void init();
    void begin() override;
    void submit(std::shared_ptr<Renderable2D> renderable) override;
    void drawString(const std::string &text, const Vector3 &position, 
      const std::shared_ptr<Font_> &font, unsigned int color) override;

    void end() override;
    void flush() override;

};
#endif