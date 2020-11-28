//
// Created by amalm on 11/28/2020.
//

#ifndef COMPUTER_GRAPHICS_PROJECT_MESHC_H
#define COMPUTER_GRAPHICS_PROJECT_MESHC_H

#include "mesh.h"
#include "shader.h"
#include "../ecs/component.h"
class MeshC : public CGEngine::Component{
    CGEngine::Mesh * model;
    Shader * program;
public:
    MeshC():Component("MeshC"){

    };
    void setmesh(CGEngine::Mesh &mod);
    void setProgram(Shader &prog);
    CGEngine::Mesh* getmesh();
    Shader* getProgram();
};


#endif //COMPUTER_GRAPHICS_PROJECT_MESHC_H
