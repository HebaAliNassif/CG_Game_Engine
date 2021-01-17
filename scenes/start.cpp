#ifndef START_H
#define START_H

#include <scene.h>
#include <camera.h>
#include <iostream>
#include <material/material_assets.h>
#include <mesh_component.h>
#include <material_component.h>
#include <mesh-utils.hpp>
#include <render_system.h>
#include <menu.cpp>
namespace CGEngine
{
    class Start : public CGEngine::Scene {
    public:

        Entity* play;
        Entity* Player;
        Transform* playerTransform;
        Transform* cameraTransform;
        Transform* enemyTransform;

        Entity* camera;

        Start(Application_Manager *manager) : Scene(manager) {
            this-> manager = manager;
            CreateMaterials();

            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex30_light_array/light_array.frag","SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex32_textured_material/light_array.frag","TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/fshaders/light_array.frag","TransShader");

            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("pacman", "assets/models/chomp.obj");
            CGEngine::mesh_utils::loadOBJ("M_letter", "assets/models/M.obj");
            CGEngine::mesh_utils::loadOBJ("P_letter", "assets/models/P.obj");
            CGEngine::mesh_utils::loadOBJ("A_letter", "assets/models/A.obj");
            CGEngine::mesh_utils::loadOBJ("N_letter", "assets/models/N.obj");
            CGEngine::mesh_utils::loadOBJ("C_letter", "assets/models/C.obj");

            //Camera Entity
            camera = createEntity("Main Camera");
            cameraTransform = camera->addComponent<Transform>();
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

            Entity* P_PACMAN = createEntity("P_PACMAN");
            P_PACMAN->addComponent<Transform>()->setLocalScale(1,1,1);
            P_PACMAN->addComponent<Mesh_Component>()->setMeshModelName("P_letter");
            P_PACMAN->addComponent<Material_Component>()->setMaterialName("letter_material");
            P_PACMAN->getComponent<Transform>()->setPosition(-2,3,0);
            P_PACMAN->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* A_1_PACMAN = createEntity("A_1_PACMAN");
            A_1_PACMAN->addComponent<Transform>()->setLocalScale(1,1,1);
            A_1_PACMAN->addComponent<Mesh_Component>()->setMeshModelName("A_letter");
            A_1_PACMAN->addComponent<Material_Component>()->setMaterialName("letter_material");
            A_1_PACMAN->getComponent<Transform>()->setPosition(-1.5,3,0);
            A_1_PACMAN->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* C_PACMAN = createEntity("C_PACMAN");
            C_PACMAN->addComponent<Transform>()->setLocalScale(1,1,1);
            C_PACMAN->addComponent<Mesh_Component>()->setMeshModelName("C_letter");
            C_PACMAN->addComponent<Material_Component>()->setMaterialName("letter_material");
            C_PACMAN->getComponent<Transform>()->setPosition(-0.8,3,0);
            C_PACMAN->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* M_PACMAN = createEntity("M_PACMAN");
            M_PACMAN->addComponent<Transform>()->setLocalScale(1,1,1);
            M_PACMAN->addComponent<Mesh_Component>()->setMeshModelName("M_letter");
            M_PACMAN->addComponent<Material_Component>()->setMaterialName("letter_material");
            M_PACMAN->getComponent<Transform>()->setPosition(0.15,3,0);
            M_PACMAN->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* A_2_PACMAN = createEntity("A_2_PACMAN");
            A_2_PACMAN->addComponent<Transform>()->setLocalScale(1,1,1);
            A_2_PACMAN->addComponent<Mesh_Component>()->setMeshModelName("A_letter");
            A_2_PACMAN->addComponent<Material_Component>()->setMaterialName("letter_material");
            A_2_PACMAN->getComponent<Transform>()->setPosition(0.7,3,0);
            A_2_PACMAN->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            Entity* N_PACMAN = createEntity("N_PACMAN");
            N_PACMAN->addComponent<Transform>()->setLocalScale(1,1,1);
            N_PACMAN->addComponent<Mesh_Component>()->setMeshModelName("N_letter");
            N_PACMAN->addComponent<Material_Component>()->setMaterialName("letter_material");
            N_PACMAN->getComponent<Transform>()->setPosition(1.4,3,0);
            N_PACMAN->getComponent<Transform>()->setEulerAngles(-90,-90,90);

            /*Entity* PACMAN = createEntity("PACMAN");
            PACMAN->addComponent<Transform>()->setLocalScale(1,1,1);
            PACMAN->addComponent<Mesh_Component>()->setMeshModelName("pacman");
            PACMAN->addComponent<Material_Component>()->setMaterialName("player_material");
            PACMAN->getComponent<Transform>()->setPosition(-3,2,0);
            PACMAN->getComponent<Transform>()->setEulerAngles(-90,-90,90);*/

        }

        void  start() override
        {
            camera->getComponent<Transform>()->setForward(glm::vec3(0,-1,0));
            camera->getComponent<Transform>()->setPosition(0, 5,0);
            camera->getComponent<Transform>()->setForward(glm::vec3(0,0,0));

        }
        bool flag_1=true , flag_2 =true;
        int time;
        void update(double deltaTime) override  {
            if(flag_1)
            {
                time = deltaTime*100;
                flag_1= false;
            }
            if( deltaTime*100> (time + 2.65) && flag_2) {
                Resource_Manager::clear();
                mesh_utils::clearMeshes();
                Material::DestroyMaterial();
                Scene *scene = new CGEngine::Menu(manager);
                manager->goToScene(scene);
                flag_2 =false;
            }
        }

    };
}
#endif //START_H

