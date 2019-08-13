#ifndef GRAPHICS_API_H
#define GRAPHICS_API_H

#include <glad/glad.h>

#include "Shader.h"
#include "Logging.h"
#include "Math/Math.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "SimpleRenderer2D.h"
#include "Renderable2D.h"
#include "BatchRenderer2D.h"
#include "Sprite.h"
#include "StaticSprite.h"
#include "TileLayer.h"
#include "Group.h"
#include "Texture.h"
#include "Label.h"
#include "FontManager.h"

class GraphicsAPI {
private:
    std::shared_ptr<Label> fps;
    std::shared_ptr<Shader> shader0;
    std::shared_ptr<Shader> shader1;
    std::shared_ptr<Shader> shader2;
    std::shared_ptr<TileLayer> layer0;
    std::shared_ptr<TileLayer> layer1;
    std::shared_ptr<TileLayer> layer2;
    std::shared_ptr<BatchRenderer2D> renderer;
    
    int mouse_x;
    int mouse_y;
    int window_w;
    int window_h;

    double delta;
    int FPS;
    
public:
    GraphicsAPI();
    ~GraphicsAPI();

    void init();
    void update();
    void render();
    void pause();
    void mousePos(int x, int y);
    void resizeViewport(int w, int h);
    void updateElapsed(const double time);
    void updateFPS(const int fps);

private:
    void close();
    void clear();
    void initOGL();
    void checkOGLError();
};

#endif // !GRAPHICS_API_H