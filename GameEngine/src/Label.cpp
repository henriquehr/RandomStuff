#include "Label.h"

Label::Label(const std::string &text, float x, float y, unsigned int color) 
  : Renderable2D(), text(text), position(Renderable2D::position), font(FontManager::get("Ubuntu")) {

    Renderable2D::position = Vector3(x, y, 0.0f);
    Renderable2D::color = color;
}

Label::Label(const std::string &text, float x, float y, std::shared_ptr<Font_> 
  font, unsigned int color)
  : Renderable2D(), text(text), position(Renderable2D::position) {

      Renderable2D::position = Vector3(x, y, 0.0f);
      Renderable2D::color = color;
}

Label::Label(const std::string &text, float x, float y, const std::string &font, 
  unsigned int color) 
  : Renderable2D(), text(text), position(Renderable2D::position), 
  font(FontManager::get(font)) {

    Renderable2D::position = Vector3(x, y, 0.0f);
    Renderable2D::color = color;
    this->validateFont(font);
}

Label::Label(const std::string &text, float x, float y, const std::string &font, 
  unsigned int size, unsigned int color) 
  : Renderable2D(), text(text), position(Renderable2D::position), 
  font(FontManager::get(font, size)) {

    Renderable2D::position = Vector3(x, y, 0.0f);
    Renderable2D::color = color;
    this->validateFont(font, size);
}

Label::~Label() {}

void Label::submit(std::shared_ptr<Renderer2D> renderer) const {
    renderer->drawString(this->text, this->position, this->font ,Renderable2D::color);
}

void Label::validateFont(const std::string &name, int size) {
    if (this->font != nullptr) {
        return;
    }
    this->font = FontManager::get("resources/Font/Ubuntu.ttf");
}
