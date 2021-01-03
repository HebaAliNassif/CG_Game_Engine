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
        RenderState * R2 = new RenderState();
        R2->setDepthEnable(GL_DEPTH_TEST);
        R2->setDepth_Function(GL_LEQUAL);
        R2->setCullEnable(GL_CULL_FACE);
        R2->setCullFace(GL_BACK);
        R2->setCullFrontFace(GL_CCW);
        R2->setCull(true);
        R2->setDepth(true);
        defaultMaterial->setRenderState(R2);


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
        RenderState * R1 = new RenderState();
        R1->setDepthEnable(GL_DEPTH_TEST);
        R1->setDepth_Function(GL_LEQUAL);
        R1->setCullEnable(GL_CULL_FACE);
        R1->setCullFace(GL_BACK);
        R1->setCullFrontFace(GL_CCW);
        R1->setCull(false);
        R1->setDepth(true);
        houseMaterial->setRenderState(R1);


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
        RenderState * R = new RenderState();
        R->setDepthEnable(GL_DEPTH_TEST);
        R->setDepth_Function(GL_LEQUAL);
        R->setCullEnable(GL_CULL_FACE);
        R->setCullFace(GL_BACK);
        R->setCullFrontFace(GL_CCW);
        R->setCull(true);
        R->setDepth(true);
//        R2->setTransparent(true);
//        R2->setBlend(true);
//        R2->setAlpha(0.2f);
//        R2->setBlendEnable(GL_BLEND);
//        R2->setBlendFunction(GL_FUNC_ADD);
//        R2->setBlendSource(GL_SRC_ALPHA);
//        R2->setBlendDestination(GL_ONE_MINUS_SRC_ALPHA);
        catMaterial->setRenderState(R);
    }
}
#endif //MATERIAL_ASSETS_H
