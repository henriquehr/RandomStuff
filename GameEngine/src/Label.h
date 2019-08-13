#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "FontManager.h"
#include "Math/Math.h"
#include "Renderable2D.h"

class Label : public Renderable2D {
public:
    std::string text;
    Vector3 position;
    std::shared_ptr<Font_> font;
    float x;
    float y;

public:
    Label(const std::string &text, float x, float y, unsigned int color);

    Label(const std::string &text, float x, float y, std::shared_ptr<Font_> font, 
      unsigned int color);
    
    Label(const std::string &text, float x, float y, const std::string &font, 
      unsigned int color);

    Label(const std::string &text, float x, float y, const std::string &font, 
      unsigned int size, unsigned int color);

    ~Label();

    void submit(std::shared_ptr<Renderer2D> renderer) const override;
    void validateFont(const std::string &name, int size=-1);
};
#endif // !LABEL_H