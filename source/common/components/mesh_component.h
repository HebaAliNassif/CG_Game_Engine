//
// Created by amalm on 11/28/2020.
//

#ifndef COMPUTER_GRAPHICS_PROJECT_MESH_COMPONENT_H
#define COMPUTER_GRAPHICS_PROJECT_MESH_COMPONENT_H

#include "mesh.h"
#include "shader/shader.h"
#include "../ecs/component.h"
namespace CGEngine {
    class Mesh_Component : public CGEngine::Component {
        CGEngine::Mesh *model;
        CGEngine::Shader *program;
    public:
        Mesh_Component() : Component("MeshC") {

        };

        void setmesh(CGEngine::Mesh &mod);

        void setProgram(Shader &prog);

        CGEngine::Mesh *getmesh();

        Shader *getProgram();

    };
}


#endif //COMPUTER_GRAPHICS_PROJECT_MESH_COMPONENT_H
