#include "material.h"


const std::string &CGEngine::Material::getShaderName() const {
    return shaderName;
}

void CGEngine::Material::setShaderName(const std::string &shaderName) {
    Material::shaderName = shaderName;
}


void CGEngine::Material::bindUniforms() const {
    for(auto &elem: listOfMaterialProperties)
    {
        //Resource_Manager::getShader(shaderName).set(elem.first,);
    }
}

CGEngine::Shader* CGEngine::Material::getShader() const {
    return Resource_Manager::getShader(shaderName);
}

int CGEngine::Material::GetShaderID() const {
    return Resource_Manager::getShader(shaderName)->programID;
}

