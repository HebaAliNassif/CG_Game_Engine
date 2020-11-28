//
// Created by amalm on 11/28/2020.
//

#include "MeshC.h"
void MeshC::setmesh(CGEngine::Mesh &mod) {
    model=&mod;
}

void MeshC::setProgram(Shader &prog) {
    program=&prog;
}
CGEngine::Mesh* MeshC::getmesh() {
    return model;
}
Shader* MeshC::getProgram()  {
    return program;
}