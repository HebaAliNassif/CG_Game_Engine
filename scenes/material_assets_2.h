#ifndef COMPUTER_GRAPHICS_PROJECT_MATERIAL_ASSETS_2_H
#define COMPUTER_GRAPHICS_PROJECT_MATERIAL_ASSETS_2_H

#pragma once
#include <material/material.h>
#include <texture/sampler.h>
namespace CGEngine {
    static void CreateMaterials2() {

        Texture* HouseTexture = Resource_Manager::loadTexture("assets/models/House/House.jpeg",1,"HouseTexture");
        Texture* CatTexture = Resource_Manager::loadTexture("assets/models/CatAlbedo.jpg",1,"CatTexture");
        Sampler* sampler = Resource_Manager::createSampler("simpleSampler");
        Texture* PacmanTexture = Resource_Manager::loadTexture("assets/models/Textures/Chomp_AlbedoTransparency.png",1,"CatTexture");
        Texture* StartTexture = Resource_Manager::loadTexture("assets/models/Textures/start.png",1,"StartTexture");
        Texture* StopTexture = Resource_Manager::loadTexture("assets/models/Textures/stop.png",1,"StopTexture");
        Texture* NameTexture = Resource_Manager::loadTexture("assets/models/Textures/pack_man.png",1,"NameTexture");
        Texture* MenuTexture = Resource_Manager::loadTexture("assets/models/Textures/next.png",1,"MenuTexture");
        Texture* GameOverTexture = Resource_Manager::loadTexture("assets/models/Textures/gameover.png",1,"GameOverTexture");
        Texture* HomeTexture = Resource_Manager::loadTexture("assets/models/Textures/home.png",1,"HomeTexture");

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
        houseMaterial->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(PacmanTexture, sampler));
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
        catMaterial->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(StartTexture, sampler));
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
        catMaterial->setRenderState(R);
        //////////////////////////////////////////////////////////////////////////////////////////
        CGEngine::Material *stop = CGEngine::Material::createMaterial("stop_material");
        stop->setShaderName("TexturedLightShader");
        stop->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(StopTexture, sampler));
        stop->addProperty<glm::vec3>("albedo_tint",{1.0f, 1.0f, 1.0f});
        stop->addProperty<glm::vec3>("specular_tint",{1.0f, 1.0f, 1.0f});
        stop->addProperty<glm::vec3>("emissive_tint",{1.0f, 1.0f, 1.0f});
        stop->addProperty<glm::vec2>("roughness_range",{0.0f, 1.0f});
        stop->addProperty<std::string>("albedo_map","white");
        stop->addProperty<std::string>("specular_map","black");
        stop->addProperty<std::string>("roughness_map","white");
        stop->addProperty<std::string>("ambient_occlusion_map","white");
        stop->addProperty<std::string>("emissive_map","black");
        RenderState * R3 = new RenderState();
        R3->setDepthEnable(GL_DEPTH_TEST);
        R3->setDepth_Function(GL_LEQUAL);
        R3->setCullEnable(GL_CULL_FACE);
        R3->setCullFace(GL_BACK);
        R3->setCullFrontFace(GL_CCW);
        R3->setCull(true);
        R3->setDepth(true);
        stop->setRenderState(R3);
        //////////////////////////////////////////
        CGEngine::Material *name = CGEngine::Material::createMaterial("gameover_material");
        name->setShaderName("TexturedLightShader");
        name->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(GameOverTexture, sampler));
        name->addProperty<glm::vec3>("albedo_tint",{1.0f, 1.0f, 1.0f});
        name->addProperty<glm::vec3>("specular_tint",{1.0f, 1.0f, 1.0f});
        name->addProperty<glm::vec3>("emissive_tint",{1.0f, 1.0f, 1.0f});
        name->addProperty<glm::vec2>("roughness_range",{0.0f, 1.0f});
        name->addProperty<std::string>("albedo_map","white");
        name->addProperty<std::string>("specular_map","black");
        name->addProperty<std::string>("roughness_map","white");
        name->addProperty<std::string>("ambient_occlusion_map","white");
        name->addProperty<std::string>("emissive_map","black");
        RenderState * R4 = new RenderState();
        R4->setDepthEnable(GL_DEPTH_TEST);
        R4->setDepth_Function(GL_LEQUAL);
        R4->setCullEnable(GL_CULL_FACE);
        R4->setCullFace(GL_BACK);
        R4->setCullFrontFace(GL_CCW);
        R4->setCull(true);
        R4->setDepth(true);
        name->setRenderState(R4);
        /////////////////////////////////////////////////////////////////////////
        CGEngine::Material *menu = CGEngine::Material::createMaterial("menu_material");
        menu->setShaderName("TexturedLightShader");
        menu->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(MenuTexture, sampler));
        menu->addProperty<glm::vec3>("albedo_tint",{1.0f, 1.0f, 1.0f});
        menu->addProperty<glm::vec3>("specular_tint",{1.0f, 1.0f, 1.0f});
        menu->addProperty<glm::vec3>("emissive_tint",{1.0f, 1.0f, 1.0f});
        menu->addProperty<glm::vec2>("roughness_range",{0.0f, 1.0f});
        menu->addProperty<std::string>("albedo_map","white");
        menu->addProperty<std::string>("specular_map","black");
        menu->addProperty<std::string>("roughness_map","white");
        menu->addProperty<std::string>("ambient_occlusion_map","white");
        menu->addProperty<std::string>("emissive_map","black");
        RenderState * R5 = new RenderState();
        R5->setDepthEnable(GL_DEPTH_TEST);
        R5->setDepth_Function(GL_LEQUAL);
        R5->setCullEnable(GL_CULL_FACE);
        R5->setCullFace(GL_BACK);
        R5->setCullFrontFace(GL_CCW);
        R5->setCull(true);
        R5->setDepth(true);
        menu->setRenderState(R5);
        ///////////////////////////////////////////
        CGEngine::Material *exit = CGEngine::Material::createMaterial("home_material");
        exit->setShaderName("TexturedLightShader");
        exit->addProperty<std::pair<Texture*,Sampler*>>("texture",std::make_pair(HomeTexture, sampler));
        exit->addProperty<glm::vec3>("albedo_tint",{1.0f, 1.0f, 1.0f});
        exit->addProperty<glm::vec3>("specular_tint",{1.0f, 1.0f, 1.0f});
        exit->addProperty<glm::vec3>("emissive_tint",{1.0f, 1.0f, 1.0f});
        exit->addProperty<glm::vec2>("roughness_range",{0.0f, 1.0f});
        exit->addProperty<std::string>("albedo_map","white");
        exit->addProperty<std::string>("specular_map","black");
        exit->addProperty<std::string>("roughness_map","white");
        exit->addProperty<std::string>("ambient_occlusion_map","white");
        exit->addProperty<std::string>("emissive_map","black");
        RenderState * R6 = new RenderState();
        R6->setDepthEnable(GL_DEPTH_TEST);
        R6->setDepth_Function(GL_LEQUAL);
        R6->setCullEnable(GL_CULL_FACE);
        R6->setCullFace(GL_BACK);
        R6->setCullFrontFace(GL_CCW);
        R6->setCull(true);
        R6->setDepth(true);
        exit->setRenderState(R6);
    }
}
#endif //MATERIAL_ASSETS_H

