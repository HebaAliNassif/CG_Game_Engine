//
// Created by amalm on 11/28/2020.
//

#ifndef COMPUTER_GRAPHICS_PROJECT_RENDERSYSTEM_H
#define COMPUTER_GRAPHICS_PROJECT_RENDERSYSTEM_H
#include"MeshC.h"
#include "../components/transform.h"
#include "entity.h"
#include "glad/gl.h"
#include "shader.h"
#include "../components/camera.h"
using namespace std;
class renderSystem {
public:
    void renderAll(vector<CGEngine::Entity*> entities);

};


#endif //COMPUTER_GRAPHICS_PROJECT_RENDERSYSTEM_H
