#ifndef LEVEL_TRANSITION_H
#define LEVEL_TRANSITION_H
#include <scene.h>
#include <camera.h>
#include <iostream>
#include <material/material_assets.h>
#include <mesh_component.h>
#include <material_component.h>
#include <mesh-utils.hpp>
#include <render_system.h>
#include <game_scene.cpp>
#include <irrKlang.h>
using namespace irrklang;
namespace CGEngine
{
    class Level_Transition : public CGEngine::Scene {
    public:
        int level;
        ISoundEngine *SoundEngine;
        Level_Transition(Application_Manager *manager, int level) : Scene(manager) {
            this-> manager = manager;
            this->level = level;
            CreateMaterials();
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex30_light_array/light_array.frag","SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex32_textured_material/light_array.frag","TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/fshaders/light_array.frag","TransShader");

            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("pacman", "assets/models/chomp.obj");
            CGEngine::mesh_utils::loadOBJ("L_letter", "assets/models/L.obj");
            CGEngine::mesh_utils::loadOBJ("E_letter", "assets/models/E.obj");
            CGEngine::mesh_utils::loadOBJ("V_letter", "assets/models/V.obj");
            CGEngine::mesh_utils::loadOBJ("1_number", "assets/models/1.obj");
            CGEngine::mesh_utils::loadOBJ("2_number", "assets/models/2.obj");

            //Camera Entity
            Entity* camera = createEntity("Main Camera");
             camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);

            Entity* Plane = createEntity("Plane");
            Plane->addComponent<Transform>()->setLocalScale(100,1,100);
            Plane->addComponent<Mesh_Component>()->setMeshModelName("plane");
            Plane->addComponent<Material_Component>()->setMaterialName("default_material");
            Plane->getComponent<Transform>()->setLocalPosition({0,0,0 });

            Entity* directional_light = createEntity("light_directional");
            directional_light->addComponent<Transform>();
            directional_light->addComponent<Light>()->setLightType(LightType::DIRECTIONAL);

            Entity* point_light = createEntity("light_point");
            point_light->addComponent<Transform>()->setPosition(0,3,0);
            point_light->getComponent<Transform>()->setEulerAngles(0,45,0);
            point_light->addComponent<Light>()->setLightType(LightType::POINT);

            //Systems
            addSystem<RenderSystem>();

            Entity* L_1_LEVEL = createEntity("L_1_LEVEL");
            L_1_LEVEL->addComponent<Transform>()->setLocalScale(1,1,1);
            L_1_LEVEL->addComponent<Mesh_Component>()->setMeshModelName("L_letter");
            L_1_LEVEL->addComponent<Material_Component>()->setMaterialName("letter_material");
            L_1_LEVEL->getComponent<Transform>()->setPosition(-1.5,3,0);
            L_1_LEVEL->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* E_1_LEVEL = createEntity("E_1_LEVEL");
            E_1_LEVEL->addComponent<Transform>()->setLocalScale(1,1,1);
            E_1_LEVEL->addComponent<Mesh_Component>()->setMeshModelName("E_letter");
            E_1_LEVEL->addComponent<Material_Component>()->setMaterialName("letter_material");
            E_1_LEVEL->getComponent<Transform>()->setPosition(-0.9,3,0);
            E_1_LEVEL->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* V_LEVEL = createEntity("V_LEVEL");
            V_LEVEL->addComponent<Transform>()->setLocalScale(1,1,1);
            V_LEVEL->addComponent<Mesh_Component>()->setMeshModelName("V_letter");
            V_LEVEL->addComponent<Material_Component>()->setMaterialName("letter_material");
            V_LEVEL->getComponent<Transform>()->setPosition(-0.3,3,0);
            V_LEVEL->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* E_2_LEVEL = createEntity("E_2_LEVEL");
            E_2_LEVEL->addComponent<Transform>()->setLocalScale(1,1,1);
            E_2_LEVEL->addComponent<Mesh_Component>()->setMeshModelName("E_letter");
            E_2_LEVEL->addComponent<Material_Component>()->setMaterialName("letter_material");
            E_2_LEVEL->getComponent<Transform>()->setPosition(0.25,3,0);
            E_2_LEVEL->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* L_2_LEVEL = createEntity("L_2_LEVEL");
            L_2_LEVEL->addComponent<Transform>()->setLocalScale(1,1,1);
            L_2_LEVEL->addComponent<Mesh_Component>()->setMeshModelName("L_letter");
            L_2_LEVEL->addComponent<Material_Component>()->setMaterialName("letter_material");
            L_2_LEVEL->getComponent<Transform>()->setPosition(0.7,3,0);
            L_2_LEVEL->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            if(level == 1) {
                Entity *NUMBER = createEntity("NUMBER");
                NUMBER->addComponent<Transform>()->setLocalScale(1, 1, 1);
                NUMBER->addComponent<Mesh_Component>()->setMeshModelName("1_number");
                NUMBER->addComponent<Material_Component>()->setMaterialName("letter_material");
                NUMBER->getComponent<Transform>()->setPosition(1.3, 3, 0);
                NUMBER->getComponent<Transform>()->setEulerAngles(-90, -90, 90);
            }
            else{
                Entity *NUMBER = createEntity("NUMBER");
                NUMBER->addComponent<Transform>()->setLocalScale(1, 1, 1);
                NUMBER->addComponent<Mesh_Component>()->setMeshModelName("2_number");
                NUMBER->addComponent<Material_Component>()->setMaterialName("letter_material");
                NUMBER->getComponent<Transform>()->setPosition(1.5, 3, 0.3);
                NUMBER->getComponent<Transform>()->setEulerAngles(-90, -90, 90);
            }

            camera->getComponent<Transform>()->setForward(glm::vec3(0,-1,0));
            camera->getComponent<Transform>()->setPosition(0, 5,0);
            camera->getComponent<Transform>()->setForward(glm::vec3(0,0,0));
        }

        void  start() override
        {
            //SoundEngine->play2D("audio/level.mp3", false);
        }

        bool flag_1=true , flag_2 =true;
        long long time;
        void update(double deltaTime) override  {
            if(flag_1)
            {
                time = deltaTime*100;
                flag_1= false;
            }
            if( deltaTime*100> (time + 0.5) && flag_2) {
                Resource_Manager::clear();
                mesh_utils::clearMeshes();
                Material::DestroyMaterial();
                //SoundEngine->drop();
                Scene *scene = new CGEngine::Game_Scene(manager, level);
                manager->goToScene(scene);
                flag_2 =false;
            }
        }
    };
}
#endif //LEVEL_TRANSITION_H

