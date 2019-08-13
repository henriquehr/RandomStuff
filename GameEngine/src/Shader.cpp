#include "Shader.h"

Shader::Shader(const char *vert_name, const char *frag_name)
: vert_name(vert_name), frag_name(frag_name) {
    this->shader_ID = this->load();
}

Shader::~Shader() {
    glDeleteProgram(this->shader_ID);
}

void Shader::enable() {
    glUseProgram(this->shader_ID);
}

void Shader::disable() {
    glUseProgram(0);
}

GLint Shader::getUniformLocation(const GLchar *name) {
    return glGetUniformLocation(this->shader_ID, name);
}

void Shader::setUniformI1(const GLchar* name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniformI1v(const GLchar* name, int *value, int count) {
    glUniform1iv(this->getUniformLocation(name), count, value);
}


void Shader::setUniformF1(const GLchar *name, float value) {
    glUniform1f(this->getUniformLocation(name), value);
}

void Shader::setUniformF1v(const GLchar *name, float *value, int count) {
    glUniform1fv(this->getUniformLocation(name), count, value);
}

void Shader::setUniformV2(const GLchar *name, const Vector2 &vector) {
    glUniform2f(this->getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniformV3(const GLchar *name, const Vector3 &vector) {
    glUniform3f(this->getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniformV4(const GLchar *name, const Vector4 &vector) {
    glUniform4f(this->getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformM4(const GLchar *name, const Matrix4 &matrix) {
    glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, matrix.matrix);
}

GLuint Shader::load() {
    GLuint program_ID = glCreateProgram();
    GLuint vertex_ID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_ID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string vertex_shader_code = Utils::loadShader(this->vert_name);

    // Read the Fragment Shader code from the file
    std::string fragment_shader_code = Utils::loadShader(this->frag_name);

    GLint result = GL_FALSE;
    int info_log_length;

    // LOG(MESSAGE) << "Compiling vertex shader " <<  this->vert_name;
    char const * vertex_source_pointer = vertex_shader_code.c_str();
    glShaderSource(vertex_ID, 1, &vertex_source_pointer, NULL);
    glCompileShader(vertex_ID);

    // Check Vertex Shader
    glGetShaderiv(vertex_ID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(vertex_ID, GL_INFO_LOG_LENGTH, &info_log_length);
        // if (info_log_length > 0) {
        std::vector<char> vertex_shader_error_message(info_log_length + 1);
        glGetShaderInfoLog(vertex_ID, info_log_length, NULL, &vertex_shader_error_message[0]);
        // }
        glDeleteShader(vertex_ID);
        LOG(ERROR) << "Error compiling the vertex shader. " << &vertex_shader_error_message[0];
    }

    // Compile Fragment Shader
    // LOG(MESSAGE) << "Compiling fragment shader " << this->frag_name;
    char const * fragment_source_pointer = fragment_shader_code.c_str();
    glShaderSource(fragment_ID, 1, &fragment_source_pointer, NULL);
    glCompileShader(fragment_ID);

    // Check Fragment Shader
    glGetShaderiv(fragment_ID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(fragment_ID, GL_INFO_LOG_LENGTH, &info_log_length);
        //if (info_log_length > 0) {
        std::vector<char> fragment_shader_error_message(info_log_length + 1);
        glGetShaderInfoLog(fragment_ID, info_log_length, NULL, &fragment_shader_error_message[0]);
        //}
        glDeleteShader(fragment_ID);
        LOG(ERROR) << "Error compiling the fragment shader. " << &fragment_shader_error_message[0];
    }

    glAttachShader(program_ID, vertex_ID);
    glAttachShader(program_ID, fragment_ID);
    glLinkProgram(program_ID);
    glValidateProgram(program_ID);

    glDeleteShader(vertex_ID);
    glDeleteShader(fragment_ID);

    return program_ID;
}