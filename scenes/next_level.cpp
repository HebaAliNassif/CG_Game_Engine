#ifndef Next_Level_H
#define Next_Level_H
#include <scene.h>
#include <camera.h>
#include <material/material_assets.h>
#include <application_manager.h>
#include <render_system.h>
#include <mesh_component.h>
#include <mesh-utils.hpp>
#include <resource_manager.h>
#include <material_component.h>
#include <right_left_controller.h>
#include <righ_left_camera_controller.h>

namespace CGEngine {
    class Next_Level : public CGEngine::Scene {
    public:
        Entity *Player;
        Box_Collider *playerCollider;
        Transform *playerTransform;
        Transform *cameraTransform;

        Box_Collider *enemyCollider;
        Transform *enemyTransform;
        Entity *camera;

        Next_Level(Application_Manager *manager) : Scene(manager) {
            CreateMaterials();
            //glClearColor(0.0,0.1,0.0, 1);
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/ex30_light_array/light_array.frag", "SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/ex32_textured_material/light_array.frag",
                                         "TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/fshaders/light_array.frag", "TransShader");

            CGEngine::mesh_utils::Cuboid("cube", false, glm::vec3(0, 0, 0), glm::vec3(2.0f, 0, 2.0f));
            CGEngine::mesh_utils::Sphere("sphere", glm::vec2(50, 50), true, glm::vec3(0, 0, 0), 0.6f);
            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("pacman", "assets/models/chomp.obj");
            CGEngine::mesh_utils::loadOBJ("enemy", "assets/models/ghost.obj");
            CGEngine::mesh_utils::Cuboid("cuboid", false, glm::vec3(0, 0, 0), glm::vec3(4.0f, 0, 4.0f));


            //Camera Entity
            camera = createEntity("Main Camera");
            cameraTransform = camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);
            camera->addComponent<RightLeftController>();

            Entity *Plane = createEntity("Plane");
            Plane->addComponent<Transform>()->setLocalScale(100, 1, 100);
            Plane->addComponent<Mesh_Component>()->setMeshModelName("plane");
            Plane->addComponent<Material_Component>()->setMaterialName("default_material");
            Plane->getComponent<Transform>()->setLocalPosition({0, 0, 0});

            Entity *directional_light = createEntity("light_directional");
            directional_light->addComponent<Transform>();
            directional_light->addComponent<Light>()->setLightType(LightType::DIRECTIONAL);

            Entity *point_light = createEntity("light_point");
            point_light->addComponent<Transform>()->setPosition(0, 1, 0);
            point_light->addComponent<Light>()->setLightType(LightType::POINT);

            Entity *spot_light = createEntity("light_spot");
            spot_light->addComponent<Transform>()->setPosition(0, 1, -10);
            spot_light->addComponent<Light>()->setLightType(LightType::SPOT);
            spot_light->getComponent<Light>()->setSpotAngle(1, 1);


            //Systems
            addSystem<RenderSystem>();
            glm::vec3 centerPosition{0, 0, 0};

            Player = createEntity("Player");
            Player->addComponent<Transform>();
            Player->addComponent<Mesh_Component>()->setMeshModelName("cube");
            Player->addComponent<Material_Component>()->setMaterialName("menu_material");
            Player->getComponent<Transform>()->setPosition(8, 10, 10);
            Player->getComponent<Transform>()->setRotation(glm::vec3(0, 1.57, 0));
            Player->addComponent<RightLeftController>();

            Entity *Stop;
            Stop = createEntity("Stop");
            Stop->addComponent<Transform>();
            Stop->addComponent<Mesh_Component>()->setMeshModelName("cube");
            Stop->addComponent<Material_Component>()->setMaterialName("stop_material");
            Stop->getComponent<Transform>()->setPosition(14, 10, 10);
            // Stop->getComponent<Transform>()->setRotation(vec3(0, 0, 0));
            Stop->addComponent<RightLeftController>();
        }

        void start() override {
            glm::vec3 Position = {11, 10, 9};
            camera->getComponent<Transform>()->setForward(glm::vec3(0, -1, 0));
            camera->getComponent<Transform>()->setPosition(Position.x, 15, Position.z);
            camera->getComponent<Transform>()->setForward(Position);
            camera->addComponent<RightLeftCamerController>();
        }

        void update(double deltaTime) override {


        }

        ~Next_Level() {

        }
    };
}
#endif //Next_Level_H

