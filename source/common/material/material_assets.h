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
        defaultMaterial->setShaderName("SimpleLightShader");
        defaultMaterial->addProperty<glm::vec3>("diffuse",{0.96, 0.9, 0.64});
        defaultMaterial->addProperty<glm::vec3>("specular",{0.5,0.3,0.1});
        defaultMaterial->addProperty<glm::vec3>("ambient",{0.5,0.3,0.1});
        defaultMaterial->addProperty<float>("shininess",5.0f);



        CGEngine::Material *houseMaterial = CGEngine::Material::createMaterial("house_material");
        houseMaterial->setShaderName("TexturedLightShader");
        houseMaterial->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(HouseTexture, sampler));
        houseMaterial->addProperty<glm::vec3>("albedo_tint",{1.0f, 1.0f, 1.0f});
        houseMaterial->addProperty<glm::vec3>("specular_tint",{1.0f, 1.0f, 1.0f});
        houseMaterial->addProperty<glm::vec3>("emissive_tint",{1.0f, 1.0f, 1.0f});
        houseMaterial->addProperty<glm::vec2>("roughness_range",{0.0f, 1.0f});
        houseMaterial->addProperty<std::string>("albedo_map","white");
        houseMaterial->addProperty<std::string>("specular_map","black");
        houseMaterial->addProperty<std::string>("roughness_map","white");
        houseMaterial->addProperty<std::string>("ambient_occlusion_map","white");
        houseMaterial->addProperty<std::string>("emissive_map","black");



        CGEngine::Material *catMaterial = CGEngine::Material::createMaterial("cat_material");
        catMaterial->setShaderName("TexturedLightShader");
        catMaterial->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(CatTexture, sampler));
        catMaterial->addProperty<glm::vec3>("albedo_tint",{1.0f, 1.0f, 1.0f});
        catMaterial->addProperty<glm::vec3>("specular_tint",{1.0f, 1.0f, 1.0f});
        catMaterial->addProperty<glm::vec3>("emissive_tint",{1.0f, 1.0f, 1.0f});
        catMaterial->addProperty<glm::vec2>("roughness_range",{0.0f, 1.0f});
        catMaterial->addProperty<std::string>("albedo_map","white");
        catMaterial->addProperty<std::string>("specular_map","black");
        catMaterial->addProperty<std::string>("roughness_map","white");
        catMaterial->addProperty<std::string>("ambient_occlusion_map","white");
        catMaterial->addProperty<std::string>("emissive_map","black");

    }
}
#endif //MATERIAL_ASSETS_H
