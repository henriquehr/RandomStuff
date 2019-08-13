#include "Font.h"

Font_::Font_(std::string name, std::string file_name, int size) 
  : name(name), file_name(file_name), size(size) {

    this->FT_Atlas = ftgl::texture_atlas_new(512, 512, 2);
    this->FT_Font = ftgl::texture_font_new_from_file(this->FT_Atlas, size, 
      this->file_name.c_str());
}

Font_::~Font_() {}
