#include "sampler.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
CGEngine::Sampler::Sampler()
{

}

void CGEngine::Sampler::generate() {

    glGenSamplers(1, &samplerID);
    glBindSampler(0, samplerID);

    glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, magnification_filter);
    glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, minification_filter);
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, wrap_s);
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, wrap_t);
    glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(border_color));
    glSamplerParameterf(samplerID, GL_TEXTURE_MAX_ANISOTROPY_EXT, max_anisotropy);
    glBindSampler(0, 0);

}

void CGEngine::Sampler::bind() const {
    glBindSampler(0, samplerID);
}

CGEngine::Sampler::~Sampler() {
    glDeleteSamplers(1, &samplerID);
}
