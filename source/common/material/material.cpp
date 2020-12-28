#include "material.h"
#include <texture/sampler.h>
std::map<std::string, CGEngine::Material*> CGEngine::Material::listOfMaterials;


const std::string &CGEngine::Material::getShaderName() const {
    return shaderName;
}

void CGEngine::Material::setShaderName(const std::string &shaderName) {
    Material::shaderName = shaderName;
}


void CGEngine::Material::bindUniforms() const {
    for(auto &property: listOfMaterialProperties)
    {
        if(property.second->Is<MaterialProperty<float>>()) {
            Resource_Manager::getShader(shaderName)->set(property.first,property.second->As<MaterialProperty<float>>()->getValue());
        }
        else if(property.second->Is<MaterialProperty<glm::vec3>>()) {
            Resource_Manager::getShader(shaderName)->set(property.first,property.second->As<MaterialProperty<glm::vec3>>()->getValue());
        }
        else if(property.second->Is<MaterialProperty<bool>>()) {
            Resource_Manager::getShader(shaderName)->set(property.first,property.second->As<MaterialProperty<bool>>()->getValue());
        }
        else if(property.second->Is<MaterialProperty<int>>()) {
            Resource_Manager::getShader(shaderName)->set(property.first,property.second->As<MaterialProperty<int>>()->getValue());
        }
        else if(property.second->Is<MaterialProperty<glm::vec2>>()) {
            Resource_Manager::getShader(shaderName)->set(property.first,property.second->As<MaterialProperty<glm::vec2>>()->getValue());
        }
        else if(property.second->Is<MaterialProperty<glm::vec4>>()) {
            Resource_Manager::getShader(shaderName)->set(property.first,property.second->As<MaterialProperty<glm::vec4>>()->getValue());
        }
        else if(property.second->Is<MaterialProperty<glm::mat4>>()) {
            Resource_Manager::getShader(shaderName)->set(property.first,property.second->As<MaterialProperty<glm::mat4>>()->getValue());
        }
        else if(property.second->Is<MaterialProperty<std::pair<Texture*,Sampler*>>>()) {
            Texture* text = property.second->As<MaterialProperty<std::pair<Texture*,Sampler*>>>()->getValue().first;
            Sampler* sam = property.second->As<MaterialProperty<std::pair<Texture*,Sampler*>>>()->getValue().second;
            //Resource_Manager::getShader(shaderName)->set(property.first,);
        }
    }
}

CGEngine::Shader* CGEngine::Material::getShader() const {
    return Resource_Manager::getShader(shaderName);
}

int CGEngine::Material::GetShaderID() const {
    return Resource_Manager::getShader(shaderName)->programID;
}

CGEngine::Material *CGEngine::Material::createMaterial(std::string materialName) {
    Material* mat = new Material();
    listOfMaterials[materialName]=mat;
    return listOfMaterials[materialName];
}

CGEngine::Material *CGEngine::Material::getMaterial(std::string materialName) {
    return listOfMaterials[materialName];
}

