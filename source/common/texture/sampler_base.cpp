#include "sampler_base.h"
#include <glm/gtc/type_ptr.hpp>

CGEngine::Sampler_Base::Sampler_Base() {}

CGEngine::Sampler_Base::~Sampler_Base() {

}

void CGEngine::Sampler_Base::setFilter(GLenum minFilter, GLenum magFilter, GLfloat max_anisotropy) {
     magnification_filter = GL_LINEAR;
     minification_filter = GL_LINEAR_MIPMAP_LINEAR;
     max_anisotropy = max_anisotropy;

}

void CGEngine::Sampler_Base::setWrap(GLenum mode) {
    wrap_s = mode;
}

void CGEngine::Sampler_Base::setLODRangeAndBias(float min, float max, float bias) {
     min_LOD = min;
     max_LOD = max;
     LOD_BIAS = bias;
}

void CGEngine::Sampler_Base::setCompareModeAndFunc(bool enable, int compareFunc) {
    comparisonMode = enable;
    comparisonModeFunc = compareFunc;
}

int CGEngine::Sampler_Base::getParameter1i(GLenum pname) {
    GLint  *k;
    glGetSamplerParameteriv(ID,pname, k);
    return (*k);
}

float CGEngine::Sampler_Base::getParameter1f(GLenum pname) {
    GLfloat  *k;
    glGetSamplerParameterfv(ID,pname, k);
    return (*k);
}

int CGEngine::Sampler_Base::getParameter1Ii(GLenum pname) {
    GLint   *k;
    glGetSamplerParameterIiv(ID,pname, k);
    return (*k);
}

unsigned CGEngine::Sampler_Base::getParameter1Iui(GLenum pname) {
    GLuint   *k;
    glGetSamplerParameterIuiv(ID,pname, k);
    return (*k);
}

const glm::vec4 CGEngine::Sampler_Base::getParameter4i(GLenum pname) {
    //glm::pt * result = glm::ivec4();
    //glGetSamplerParameteriv(ID,pname, result);
    return  glm::ivec4();
}

const glm::vec4 CGEngine::Sampler_Base::getParameter4f(GLenum pname) {
    return glm::vec4();
}

const glm::vec4 CGEngine::Sampler_Base::getParameter4Ii(GLenum pname) {
    return glm::vec4();
}

const glm::vec4 CGEngine::Sampler_Base::getParameter4Iui(GLenum pname) {
    return glm::vec4();
}
