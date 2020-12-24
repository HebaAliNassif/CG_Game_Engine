#ifndef SAMPLER_H
#define SAMPLER_H
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
namespace CGEngine {
    class Sampler {
    public:
        GLuint samplerID;

        Sampler();

        GLenum magnification_filter = GL_LINEAR, minification_filter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrap_s = GL_REPEAT, wrap_t = GL_REPEAT;
        glm::vec4 border_color = {1,1,1,1};
        GLfloat max_anisotropy = 1.0f;

        void generate();
        void bind() const;

    };
}

#endif //SAMPLER_H
