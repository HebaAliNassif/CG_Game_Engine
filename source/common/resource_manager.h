#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <application_manager.h>
#include <map>
#include <string>
#include <shader/shader.h>
#include <texture/texture.h>
namespace CGEngine {
    class Resource_Manager {
    public:
        //Map for all created shaders
        static std::map<std::string, Shader> Shaders;
        //Map for all created Textures
        static std::map<std::string, Texture>Textures;

        // loads (and generates) a texture from file
        static Texture* loadTexture(const char *file, bool alpha, std::string name);
        // retrieves a stored texture
        static Texture* getTexture(std::string name);

        //Loads a shader program from the given vertex and fragment shader's source code
        static Shader* LoadShader(const char *vertexShaderFileName, const char *fragmentShaderFileName, std::string shaderName);
        // retrieves a stored shader
        static Shader* getShader(std::string name);

        static void clear();

    private:
        //Roads a single texture from file
        static Texture readTextureFromFile(const char *file, bool alpha);
        //Reads and generates a shader program
        static Shader readShaderFromFile(const char *vertexShaderFileName, const char *fragmentShaderFileName);

    };
}

#endif //RESOURCE_MANAGER_H
