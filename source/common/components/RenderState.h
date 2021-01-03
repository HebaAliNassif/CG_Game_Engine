//
// Created by amalm on 12/27/2020.
//

#ifndef COMPUTER_GRAPHICS_PROJECT_RENDERSTATE_H
#define COMPUTER_GRAPHICS_PROJECT_RENDERSTATE_H
#include <application_manager.h>
namespace CGEngine {

    class RenderState {
        GLenum cull_enable
        ,cull_face,gl_front_face,depth_enable,depth_func,blend_enable,blend_func
        ,blend_source,blend_dest;
        bool transparent, cull, depth,blend;
        float render_alpha;
    public:


        void setCullEnable(GLenum enable );

        void setCullFace(GLenum cullface );

        void setCullFrontFace(GLenum face );

        void setDepthEnable(GLenum depthenable);

        void setDepth_Function(GLenum depthfunc);

        void setBlendEnable(GLenum blendenable);

        void setBlendFunction(GLenum blendfunc);

        void setBlendSource(GLenum blendsource);

        void setBlendDestination(GLenum blenddest);

        void setTransparent(bool trans);

        void setCull(bool C);

        void setDepth(bool D);

        void setBlend(bool B);

        void setAlpha(float alpha);

        GLenum getCullEnable();

        GLenum getCullFace();

        GLenum getCullFrontFace();

        GLenum getDepthFunction();

        GLenum getDepthEnable();

        GLenum getBlendEnable();

        GLenum getBlendFunction();

        GLenum getBlendSource();

        GLenum getBlendDestination();

        bool getTransparent();

        bool getCull();

        bool getDepth();

        bool getBlend();

        float getAlpha();

    };
}


#endif //COMPUTER_GRAPHICS_PROJECT_RENDERSTATE_H
