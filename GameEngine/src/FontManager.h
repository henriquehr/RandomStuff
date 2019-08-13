#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <memory>
#include <vector>

#include "Logging.h"
#include "Font.h"

class FontManager {
private:
    static std::vector<std::shared_ptr<Font_>> fonts;

private:
    FontManager();
    ~FontManager();

public:
    static void add(std::shared_ptr<Font_> font);
    static std::shared_ptr<Font_> get(const std::string &name);
    static std::shared_ptr<Font_> get(const std::string &name, unsigned int size);
    static void clean();
};
#endif // !FONT_MANAGER_H