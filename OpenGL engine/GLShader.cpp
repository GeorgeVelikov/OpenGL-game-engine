#include "stdafx.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include "headers/GLShader.h"

Shader::Shader(const char *vPath, const char *fPath) {
    std::string         vCode,      fCode;
    std::ifstream       vSFile,     fSFile;
    std::stringstream   vSStream,   fSStream;
    vSFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fSFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open file
        vSFile.open(vPath);         fSFile.open(fPath);
        // readbuffer
        vSStream << vSFile.rdbuf(); fSStream << fSFile.rdbuf();
        // close files
        vSFile.close();             fSFile.close();
        // put stream to code vars
        vCode = vSStream.str();     fCode = fSStream.str();
    }

    catch (std::ifstream::failure ex) { std::cout << "Error: shader cannot be read"; }

    const char *vSCode = vCode.c_str();
    const char *fSCode = fCode.c_str();
    
    unsigned int vertex, fragment;
    int noErrors;

    // compile vertex shader and check if all is well
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vSCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &noErrors);
    if (!noErrors) { std::cout << "Error: vertex shader failed to compile"; }

    // compile fragment shader and check if all is well
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fSCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &noErrors);
    if (!noErrors) { std::cout << "Error: fragment shader failed to compile"; }

    // link shaders and check if all is well
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &noErrors);
    if (!noErrors) { std::cout << "Error: shader linking failed"; }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() { 
    glUseProgram(id); 
}
// ----------------------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
// ----------------------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}
// ----------------------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
// ----------------------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}
// ----------------------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ----------------------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ----------------------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ----------------------------------------------------------------------------------------