#include "GraphicsAPI.h"

GraphicsAPI::GraphicsAPI()
  : mouse_x(0), mouse_y(0), window_w(640), window_h(480) {
    LOG(MESSAGE) << "Graphics API loaded.";
}

GraphicsAPI::~GraphicsAPI() {
    FontManager::clean();
    this->close();
}

void GraphicsAPI::init() {
    // if (this->getState() == GraphicsAPI::STATE::INITIALIZED || this->getState() == GraphicsAPI::STATE::PAUSED) {
    //     LOG(WARNING) << "Graphics API already initialized.";
    //     return;
    // }
    this->initOGL();

    FontManager::add(std::make_shared<Font_>("Ubuntu", "resources/Font/Ubuntu.ttf", 32));

    Matrix4 ortho = Matrix4::createOrthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
    
    shader0 = std::make_shared<Shader>("basic.vert", "basic.frag");
    shader0->enable();
    shader0->setUniformV2("light_pos", Vector2(4.0f, 1.5f));    

    layer0 = std::make_shared<TileLayer>(shader0);

    std::vector<std::shared_ptr<Texture>> textures = {
        std::make_shared<Texture>("test0.png"),
        std::make_shared<Texture>("test1.png"),
        std::make_shared<Texture>("test2.png"),
        std::make_shared<Texture>("test3.png")
    };

    for (float y = -9.0f; y < 9.0f; y++) {
         for (float x = -16.0f; x < 16.0f; x++) {
            if (rand() % 4 == 0) {
                layer0->add(std::make_shared<Sprite>(x, y, 0.9f, 0.9f, 0xffffffff));

            } else {
                layer0->add(std::make_shared<Sprite>(x, y, 0.9f, 0.9f, 
                  textures[rand() % textures.size()]));
            }
        }
    }

    std::shared_ptr<Group> g =  std::make_shared<Group>(Matrix4::createTranslation(Vector3(-15.8f, 7.0f, 0.0f)));
    fps = std::make_shared<Label>("", 0.4f, 0.4f, "Ubuntu", 32, 0xff000000);
    g->add(std::make_shared<Sprite>(0, 0, 5, 1.5f, 0xff808080));
    g->add(fps);

    layer0->add(g);

    GLint texIDs[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    };

    shader0->enable();
    shader0->setUniformI1v("textures", texIDs, 10);
    shader0->setUniformM4("pr_matrix", Matrix4::createOrthographic(-16.0f, 16.0f,
      -9.0f, 9.0f, -1.0f, 1.0f));

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    LOG(MESSAGE) << "OpenGL version: " << glGetString(GL_VERSION);
    LOG(MESSAGE) << "Graphics initialized.";
}

void GraphicsAPI::update() {
    //LOG(MESSAGE) << "Graphics API updated.";
}

void GraphicsAPI::render() {
    this->clear();
    
    // shader0->enable();
    shader0->setUniformV2("light_pos", Vector2((float)(this->mouse_x * 32.0f / 
      this->window_w - 16.0f), (float)(9.0f - this->mouse_y * 18.0f / this->window_h)));
    
    // shader0->setUniformM4("ml_matrix", Matrix4::createRotation(60.0f * 
    //   this->delta, Vector3(0,0,1)));

    layer0->render();

    fps->text = std::to_string(this->FPS) + "fps";

    this->checkOGLError();
}

void GraphicsAPI::pause() {
    // this->setState(GraphicsAPI::STATE::PAUSED);
    LOG(MESSAGE) << "Graphics API paused.";
}

inline void GraphicsAPI::close() {
    // this->setState(GraphicsAPI::STATE::CLOSED);
    LOG(MESSAGE) << "Graphics API closed.";
}

inline void GraphicsAPI::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void GraphicsAPI::initOGL() {
    int glad_init = gladLoadGL();
    if (!glad_init) {
        LOG(ERROR) << "Unable to initialize glad.";
    }
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

inline void GraphicsAPI::checkOGLError() {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        LOG(ERROR) << "OPENGL ERROR: " << error;
    }
}

void GraphicsAPI::mousePos(int x, int y) {
    this->mouse_x = x;
    this->mouse_y = y;
}

void GraphicsAPI::resizeViewport(int w, int h) {
    this->window_w = w;
    this->window_h = h;
    glViewport(0, 0, w, h);
}

void GraphicsAPI::updateElapsed(const double time) {
    this->delta = time / 1000.0f ;
}
void GraphicsAPI::updateFPS(const int fps) {
    this->FPS = fps;
}
