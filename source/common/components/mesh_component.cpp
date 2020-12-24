//
// Created by amalm on 11/28/2020.
//

#include "mesh_component.h"
void CGEngine::Mesh_Component::setmesh(CGEngine::Mesh &mod) {
    model=&mod;
}

void CGEngine::Mesh_Component::setProgram(Shader &prog) {
    program=&prog;
}
CGEngine::Mesh* CGEngine::Mesh_Component::getmesh() {
    return model;
}
CGEngine::Shader* CGEngine::Mesh_Component::getProgram()  {
    return program;
}