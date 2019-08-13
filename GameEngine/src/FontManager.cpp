#include "FontManager.h"

std::vector<std::shared_ptr<Font_>> FontManager::fonts;

FontManager::FontManager() {}

FontManager::~FontManager() {}

void FontManager::add(std::shared_ptr<Font_> font) {
    fonts.push_back(font);
}

std::shared_ptr<Font_> FontManager::get(const std::string &name) {
    for (int i = 0; i < fonts.size(); i++){
        if (fonts[i]->getName() == name) {
            return fonts[i];
        }
    }
    LOG(ERROR) << "Font not found. " << name;
    return nullptr;
}

std::shared_ptr<Font_> FontManager::get(const std::string &name, unsigned int size) {
    for (int i = 0; i < fonts.size(); i++) {
        if (fonts[i]->getSize() == size && fonts[i]->getName() == name) {
            return fonts[i];
        }
    }
    LOG(ERROR) << "Font not found. " << name << " - " << size;
    return nullptr;
}

void FontManager::clean() {
    // for (int i = 0; i < fonts.size(); i++) {
    //     delete fonts[i];
    // }
    fonts.clear();
}
