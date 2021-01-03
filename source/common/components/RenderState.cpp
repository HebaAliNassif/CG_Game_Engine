//
// Created by amalm on 12/27/2020.
//

#include "RenderState.h"
#include <application_manager.h>

void CGEngine::RenderState::setCullEnable(GLenum enable) {

    cull_enable=enable;
}
void CGEngine::RenderState::setCullFace(GLenum cullface) {

 cull_face=cullface;
}
void CGEngine::RenderState::setCullFrontFace(GLenum face )
{
    gl_front_face=face;
}
void CGEngine::RenderState::setDepthEnable(GLenum depthenable)
{
  depth_enable=depthenable;
}

void CGEngine::RenderState::setBlendEnable(GLenum blendenable) {

    blend_enable=blendenable;
}
void CGEngine::RenderState::setDepth_Function(GLenum depthfunction)
{
    depth_func=depthfunction;
}
void CGEngine::RenderState::setBlendFunction(GLenum blendfunc)
{
blend_func=blendfunc;
}
void CGEngine::RenderState::setBlendSource(GLenum blendsource)
{
blend_source=blendsource;
}

void CGEngine::RenderState::setBlendDestination(GLenum blenddest)
{
 blend_dest=blenddest;
}
void CGEngine::RenderState::setAlpha(float alpha)
{
  render_alpha=alpha;
}

void CGEngine::RenderState::setCull(bool C){
    cull=C;
}

void CGEngine::RenderState::setDepth(bool D){
   depth=D;
}
void CGEngine::RenderState::setBlend(bool B)
{
blend=B;
}


GLenum CGEngine::RenderState::getCullEnable()
{

 return cull_enable;
}

GLenum CGEngine::RenderState::getCullFace()
{
return cull_face;
}

GLenum CGEngine::RenderState::getCullFrontFace()
{
return gl_front_face;
}
GLenum CGEngine::RenderState::getDepthFunction()
{
    return depth_func;
}
GLenum CGEngine::RenderState::getDepthEnable()
{
    return depth_enable;
}
GLenum CGEngine::RenderState::getBlendEnable()
{
    return blend_enable;
}
GLenum CGEngine::RenderState::getBlendFunction()
{
    return blend_func;
}
GLenum CGEngine::RenderState::getBlendSource()
{
    return blend_source;
}
GLenum CGEngine::RenderState::getBlendDestination()
{
return blend_dest;
}
void CGEngine::RenderState::setTransparent(bool trans)
{
     transparent=trans;
}
bool  CGEngine::RenderState::getTransparent()
{
return transparent;
}
bool CGEngine::RenderState::getCull()
{
    return cull;

}

bool CGEngine::RenderState::getDepth()
{
    return depth;
}
bool CGEngine::RenderState::getBlend() {

    return blend;
}
float CGEngine::RenderState::getAlpha()
{
    return render_alpha;
}