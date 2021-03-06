//
// Created by Heba on 04/11/2020.
//

#include "shader.h"
#include <iostream>
#include <fstream>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void CGEngine::Shader::Compile(const char* vertexSource, const char* fragmentSource)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompilationErrors(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompilationErrors(fragmentShader);

    this->programID = glCreateProgram();

    glAttachShader(this->programID, vertexShader);
    glAttachShader(this->programID, fragmentShader);

    glLinkProgram(this->programID);
    checkProgramLinkingErrors(this->programID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

}

void CGEngine::Shader::checkShaderCompilationErrors(GLuint shader){
    //Check and log for any error in the compilation process.
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);          // Takes a shader and returns the status of this shader program.
    if(!status){                                                // If there is a status (status != 0):
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);     // Get the error length (char array length).
        char* logStr = new char[length];
        glGetShaderInfoLog(shader, length, nullptr, logStr);    // Get the error char array.
        std::cerr << "ERROR:" << logStr << std::endl;           // print the char array of the log error.
        delete[] logStr;
        std::exit(-1);
    }
}
void CGEngine::Shader::checkProgramLinkingErrors(GLuint program){
    //Check and log for any error in the linking process.
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);               // Takes a shader program (vertex & fragment) and returns the status of this shader program.
    if (!status)                                                    // If there is a status (status != 0):
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);       // Get the error length (char array length).
        char* logStr = new char[length];
        glGetProgramInfoLog(program, length, nullptr, logStr);      // Get the error char array.
        std::cerr << "LINKING ERROR: " << logStr << std::endl;      // print the char array of the log error.
        delete[] logStr;
        std::exit(-1);
    }
}

GLuint CGEngine::Shader::getUniformLocation(const std::string &name) {
    // It is not efficient to ask OpenGL for Uniform location everytime we need them
    // So the first time they are needed, we cache them in a map and reuse them whenever needed again
    auto it = uniform_location_cache.find(name);
    if(it != uniform_location_cache.end()){
        return it->second; // We found the uniform in our cache, so no need to call OpenGL.
    }
    GLuint location = glGetUniformLocation(this->programID, name.c_str()); // The uniform was not found, so we retrieve its location
    uniform_location_cache[name] = location; // and cache the location for later queries
    return location;
}

CGEngine::Shader &CGEngine::Shader::useShaderProgram()
{
    glUseProgram(this->programID);
    return *this;
}

void CGEngine::Shader::set(const std::string &uniform, GLfloat value, bool useShader) {
    if (useShader)
        this->useShaderProgram();
    glUniform1f(getUniformLocation(uniform), value);
}

void CGEngine::Shader::set(const std::string &uniform, GLint value, bool useShader) {
    if (useShader)
        this->useShaderProgram();
    glUniform1i(getUniformLocation(uniform), value);
}

void CGEngine::Shader::set(const std::string &uniform, GLboolean value, bool useShader) {
    if (useShader)
        this->useShaderProgram();
    glUniform1i(getUniformLocation(uniform), value);
}

void CGEngine::Shader::set(const std::string &uniform, glm::vec2 value, bool useShader) {
    if (useShader)
        this->useShaderProgram();
    glUniform2f(getUniformLocation(uniform), value.x, value.y);
}

void CGEngine::Shader::set(const std::string &uniform, glm::vec3 value, bool useShader) {
    if (useShader)
        this->useShaderProgram();
    glUniform3f(getUniformLocation(uniform), value.x, value.y, value.z);
}

void CGEngine::Shader::set(const std::string &uniform, glm::vec4 value, bool useShader) {
    if (useShader)
        this->useShaderProgram();
    glUniform4f(getUniformLocation(uniform),  value.x, value.y, value.z, value.w);
}

void CGEngine::Shader::set(const std::string &uniform, glm::mat4 value, GLboolean transpose, bool useShader) {
    if (useShader)
        this->useShaderProgram();
    glUniformMatrix4fv(getUniformLocation(uniform),  1, transpose, glm::value_ptr(value));
}

CGEngine::Shader::~Shader() {
    glDeleteProgram(programID);
}

