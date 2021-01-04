#include "resource_manager.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <fstream>
#include <iostream>

std::map<std::string, CGEngine::Shader*> CGEngine::Resource_Manager::Shaders;
std::map<std::string, CGEngine::Texture*> CGEngine::Resource_Manager::Textures;
std::map<std::string, CGEngine::Sampler*> CGEngine::Resource_Manager::Samplers;

std::string read_file(const char* filename){
    std::ifstream fin(filename);
    if(fin.fail()){
        std::cerr << "Unable to open shader file: " << filename << std::endl;
        std::exit(-1);
    }
    return std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
}

CGEngine::Texture* CGEngine::Resource_Manager::loadTexture(const char *file, bool alpha, std::string name) {
    Textures[name] = readTextureFromFile(file, alpha);
    return Textures[name];
}

CGEngine::Texture* CGEngine::Resource_Manager::getTexture(std::string name) {
    return Textures[name];
}

CGEngine::Texture* CGEngine::Resource_Manager::readTextureFromFile(const char *file, bool alpha) {
    Texture* texture = new Texture();
    if (alpha)
    {
        texture->Internal_Format = GL_RGBA8;
        texture->Image_Format = GL_RGBA;
    }
    stbi_set_flip_vertically_on_load(true);
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 4);
    // now generate texture
    texture->generate(width, height, data);

    // and finally free image data
    stbi_image_free(data);

    return texture;
}

CGEngine::Shader* CGEngine::Resource_Manager::LoadShader(const char *vertexShaderFileName, const char *fragmentShaderFileName, std::string shaderName)
{
    Shaders[shaderName] = readShaderFromFile(vertexShaderFileName, fragmentShaderFileName);
    return Shaders[shaderName];
}
CGEngine::Shader* CGEngine::Resource_Manager::getShader(std::string name)
{
    return Shaders[name];
}

CGEngine::Shader* CGEngine::Resource_Manager::readShaderFromFile(const char *vertexShaderFileName, const char *fragmentShaderFileName){
    std::string vertexShaderSourceCode;
    std::string fragmentShaderSourceCode;
    try
    {
        vertexShaderSourceCode= read_file(vertexShaderFileName);
        fragmentShaderSourceCode= read_file(fragmentShaderFileName);
    }
    catch (std::exception e) {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vertexShaderSourceCodeAsCStr = vertexShaderSourceCode.c_str();
    const char* fragmentShaderSourceCodeAsCStr = fragmentShaderSourceCode.c_str();

    Shader* shader = new Shader();
    shader->Compile(vertexShaderSourceCodeAsCStr, fragmentShaderSourceCodeAsCStr);
    return shader;
}

void CGEngine::Resource_Manager::clear() {

    for (auto &iter : Shaders) {
        delete iter.second;
    }
    for (auto iter : Textures) {
        delete iter.second;
    }
    for (auto iter : Samplers) {
        delete iter.second;
    }

    Shaders.clear();
    Textures.clear();
    Samplers.clear();
}

CGEngine::Sampler *CGEngine::Resource_Manager::createSampler(std::string name) {
    Sampler* sampler = new Sampler();
    Samplers[name] = sampler;
    return sampler;
}

CGEngine::Sampler *CGEngine::Resource_Manager::getSampler(std::string name) {
    return Samplers[name];
}

