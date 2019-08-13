#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <vector>
#include <glad/glad.h>

#include "Utils.h"
#include "Logging.h"
#include "Math/Math.h"

class Shader {
public:
    GLuint shader_ID;

private:
    const char *vert_name;
    const char *frag_name;

public:
    Shader(const char *vert_name, const char *frag_name);
    Shader() {}
    ~Shader();

    void enable();
    void disable();
    void setUniformI1(const GLchar* name, int value);
    void setUniformI1v(const GLchar* name, int *value, int count);
    void setUniformF1(const GLchar *name, float value);
    void setUniformF1v(const GLchar *name, float *value, int count);
    void setUniformV2(const GLchar *name, const Vector2 &vector);
    void setUniformV3(const GLchar *name, const Vector3 &vector);
    void setUniformV4(const GLchar *name, const Vector4 &vector);
    void setUniformM4(const GLchar *name, const Matrix4 &matrix);

private:
    GLint getUniformLocation(const GLchar *name);
    GLuint load();
};
#endif // !SHADER_H