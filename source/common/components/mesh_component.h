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

        std::string meshModelName;

    public:
        Mesh_Component() : Component("MeshC") {

        };

        const std::string &getMeshModelName() const;

        void setMeshModelName(const std::string &meshModelName);



    };
}


#endif //COMPUTER_GRAPHICS_PROJECT_MESH_COMPONENT_H
