#include "stdafx.h"
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

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}