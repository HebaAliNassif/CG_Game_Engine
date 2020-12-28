#include "mesh_component.h"

const std::string &CGEngine::Mesh_Component::getMeshModelName() const {
    return meshModelName;
}

void CGEngine::Mesh_Component::setMeshModelName(const std::string &meshModelName) {
    Mesh_Component::meshModelName = meshModelName;
}
