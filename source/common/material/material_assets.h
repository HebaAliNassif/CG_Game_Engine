#ifndef MATERIAL_ASSETS_H
#define MATERIAL_ASSETS_H
#pragma once
#include <material/material.h>
#include <texture/sampler.h>
namespace CGEngine {
    static void CreateMaterials() {
        CGEngine::Material *defaultMaterial = CGEngine::Material::createMaterial("default_material");
        defaultMaterial->setShaderName("simpleShader");
        defaultMaterial->addProperty<glm::vec3>("diffuse", glm::vec3(0, 0, 0));


        Texture* HouseTexture = Resource_Manager::loadTexture("assets/models/House/House.jpeg",1,"HouseTexture");
        HouseTexture->bind();
        Sampler* sampler = new Sampler();
        CGEngine::Material *houseMaterial = CGEngine::Material::createMaterial("house_material");
        houseMaterial->setShaderName("3dShader");
        houseMaterial->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(HouseTexture,sampler));

    }
}
#endif //MATERIAL_ASSETS_H
