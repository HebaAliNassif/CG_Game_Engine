#include "texture.h"
#include <stb/stb_image.h>


CGEngine::Texture::Texture(): Width(0), Height(0), Internal_Format(GL_RGBA8), Image_Format(GL_RGBA)
{
    glGenTextures(1, &this->textureID);
}

GLuint CGEngine::Texture::getTextureID() const
{
    return this->textureID;
}

void CGEngine::Texture::generate(unsigned int width, unsigned int height, unsigned char *data) {
    this->Width = width;
    this->Height = height;

    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // set Texture wrap and filter modes
   /* glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);*/
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void CGEngine::Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}

