#ifndef MATERIAL_ASSETS_H
#define MATERIAL_ASSETS_H
#pragma once
#include <material/material.h>
#include <texture/sampler.h>
namespace CGEngine {
    static void CreateMaterials() {

        Texture* HouseTexture = Resource_Manager::loadTexture("assets/models/House/House.jpeg",1,"HouseTexture");
        Texture* CatTexture = Resource_Manager::loadTexture("assets/models/CatAlbedo.jpg",1,"CatTexture");

        Sampler* sampler = new Sampler();

        CGEngine::Material *defaultMaterial = CGEngine::Material::createMaterial("default_material");
        defaultMaterial->setShaderName("DirectionalLightShader");
        defaultMaterial->addProperty<glm::vec3>("diffuse", glm::vec3(0, 0, 0));
        defaultMaterial->addProperty<float>("specular", 50.0f);

        //std::cout<<"Before update: "<<defaultMaterial->getPropertyValue<float>("specular")<<"\n";
        //defaultMaterial->updatePropertyValue<float>("specular",60.0f);
        //std::cout<<"After update: "<<defaultMaterial->getPropertyValue<float>("specular")<<"\n";


        CGEngine::Material *houseMaterial = CGEngine::Material::createMaterial("house_material");
        houseMaterial->setShaderName("3dShader");
        houseMaterial->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(HouseTexture, sampler));

        CGEngine::Material *catMaterial = CGEngine::Material::createMaterial("cat_material");
        catMaterial->setShaderName("3dShader");
        catMaterial->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(CatTexture, sampler));

    }
}
#endif //MATERIAL_ASSETS_H
