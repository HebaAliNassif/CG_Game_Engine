#include "material.h"

CGEngine::Material::Material():Component("Material")
{

}

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

