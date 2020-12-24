#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <component.h>
#include <map>
#include <string>

namespace CGEngine {
    class Texture {

    public:
        Texture();

        GLuint getTextureID() const;

        // generates texture from image data
        void generate(unsigned int width, unsigned int height, unsigned char* data);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void bind() const;

        // texture image dimensions
        unsigned int Width, Height; // width and height of loaded image in pixels

        // texture Format
        unsigned int Internal_Format; // format of texture object
        unsigned int Image_Format; // format of loaded image

        GLfloat shineDamper;
        GLfloat reflectivity;
        GLuint textureID;
    };
}
#endif //TEXTURE_H
