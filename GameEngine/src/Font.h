#ifndef FONT_H
#define FONT_H

#include <string>

#include <glad/glad.h>

#include "Logging.h"

#include "../third_party/freetype-gl/freetype-gl.h"

class Font_ { // Conflict
public:
    ftgl::texture_atlas_t *FT_Atlas;
    ftgl::texture_font_t *FT_Font;
    std::string name;
    std::string file_name;
    unsigned int size;

public:
    Font_(std::string name, std::string file_name, int size);
    ~Font_();

    inline ftgl::texture_font_t* getFTFont() const {
        return this->FT_Font;
    }

    inline const unsigned int getID() const {
        return this->FT_Atlas->id;
    }

    inline const std::string& getName() const {
        return this->name;
    }

    inline const std::string& getFileName() const {
        return this->file_name;
    }

    inline const int getSize() const {
        return this->size;
    }
};
#endif // !FONT_H