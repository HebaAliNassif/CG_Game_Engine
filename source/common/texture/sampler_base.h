#ifndef SAMPLER_BASE_H
#define SAMPLER_BASE_H
#include <glad/gl.h>
#include <glm/glm.hpp>
namespace CGEngine {

    class Sampler_Base {

        GLuint ID;

        GLenum magnification_filter = GL_LINEAR, minification_filter = GL_LINEAR_MIPMAP_LINEAR;
        GLenum wrap_s = GL_REPEAT, wrap_t = GL_REPEAT;
        glm::vec4 border_color = {1,1,1,1};
        GLfloat max_anisotropy = 1.0f;
        float min_LOD, max_LOD, LOD_BIAS;

        bool comparisonMode = false;
        bool comparisonModeFunc = GL_LEQUAL;
    public:
        Sampler_Base();

        virtual ~Sampler_Base();

        //Set minification and magnification filter, and maximum anisotropy for anisotropic filtering. More...
        //minFilter	can be GL_NEAREST, GL_LINEAR or GL_{NEAREST|LINEAR}_MIPMAP_{NEAREST|LINEAR}
        //maxFilter	can be GL_NEAREST or GL_LINEAR
        //anisotropy	anisotropic filtering is enabled by setting anisotropy to a value different from 1.0 (GL_TEXTURE_MAX_ANISOTROPY_EXT property).
        void setFilter(GLenum minFilter, GLenum magFilter, GLfloat anisotropy = 1.0);

        //Set wrap mode. More...
        //mode	GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, ...
        void setWrap(GLenum mode);

        //Set LOD range and bias for mipmap image selection.
        void setLODRangeAndBias(float min, float max, float bias);

        //Depth texture comparison mode fetching for use with GLSL shadow sampler.
        void setCompareModeAndFunc(bool enable = true, int compareFunc = GL_LEQUAL);

        //pure virtual member function for actually setting and retrieving parameters
        virtual void setParameter(GLenum pname, int value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void setParameter(GLenum pname, float value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void setParameter(GLenum pname, int *value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void setParameter(GLenum pname, float *value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void setParameterI(GLenum pname, int *value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void setParameterI(GLenum pname, unsigned *value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void getParameter(GLenum pname, int *value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void getParameter(GLenum pname, float *value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void getParameterI(GLenum pname, int *value) = 0;

        //pure virtual member function for actually setting and retrieving parameters
        virtual void getParameterI(GLenum pname, unsigned *value) = 0;

        //Retrieve single valued integer parameter.
        int getParameter1i(GLenum pname);

        //Retrieve single valued float parameter.
        float getParameter1f(GLenum pname);

        //Retrieve single valued integer parameter.
        int getParameter1Ii(GLenum pname);

        //Retrieve single valued unsigned integer parameter.
        unsigned getParameter1Iui(GLenum pname);

        //Retrieve quad-valued integer parameters.
        const glm::vec4 getParameter4i(GLenum pname);

        //Retrieve quad-valued float parameters.
        const glm::vec4 getParameter4f(GLenum pname);

        //Retrieve quad-valued integer parameters.
        const glm::vec4 getParameter4Ii(GLenum pname);

        //Retrieve quad-valued unsigned integer parameters.
        const glm::vec4 getParameter4Iui(GLenum pname);

    };
}


#endif //SAMPLER_BASE_H
