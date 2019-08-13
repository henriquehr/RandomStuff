#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include <FreeImage.h>

#include "Logging.h"

#define RESOURCES_PATH "resources/"
#define IMAGES_PATH RESOURCES_PATH << "Image/"
#define SHADERS_PATH RESOURCES_PATH << "Shader/"
#define AUDIO_PATH RESOURCES_PATH << "Audio/"
#define FONTS_PATH RESOURCES_PATH << "Font/"
#define MESHES_PATH RESOURCES_PATH << "Mesh/"

class Utils {
public:
    Utils();
    ~Utils();

    inline static BYTE* loadImage(const char *file_name, GLsizei *width, GLsizei *height) {
        std::ostringstream oss;
        oss << IMAGES_PATH << file_name ;
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        FIBITMAP *dib = nullptr;
        fif = FreeImage_GetFileType(oss.str().c_str(), 0);
        if (fif == FIF_UNKNOWN) {
            fif = FreeImage_GetFIFFromFilename(oss.str().c_str());
        }
        if (fif == FIF_UNKNOWN) {
            LOG(ERROR) << "Error loading image. " << oss.str();
        }
        if (FreeImage_FIFSupportsReading(fif)) {
            dib = FreeImage_Load(fif, oss.str().c_str());
        }
        if (!dib) {
            LOG(ERROR) << "Error loading image. " << oss.str();
        }
        BYTE* pixels = FreeImage_GetBits(dib);
        *width = FreeImage_GetWidth(dib);
        *height = FreeImage_GetHeight(dib);
        int bits = FreeImage_GetBPP(dib);
        int size = *width * *height * (bits / 8);
        BYTE* result = new BYTE[size];
        memcpy(result, pixels, size);
        FreeImage_Unload(dib);
        return result;
    }

    inline static std::string loadShader(const char *file_name) {
        std::ostringstream file_path;
        file_path << SHADERS_PATH << file_name;
        return loadTXTFile(file_path);
    }

private:
    inline static std::string loadTXTFile(const std::ostringstream &path) {
        std::ifstream ifs(path.str());
        std::string content(std::istreambuf_iterator<char>(ifs.rdbuf()), 
          std::istreambuf_iterator<char>());

        return content;
    }
};

#endif // !UTILS_H