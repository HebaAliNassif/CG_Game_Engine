#include <scene.h>
#include <camera.h>
#include <iostream>
#include <material_assets_2.h>
#include <mesh_component.h>
#include <material_component.h>
#include <mesh-utils.hpp>
#include <render_system.h>
namespace CGEngine
{
    class Menu : public CGEngine::Scene {
    public:

        Entity* play;
        Entity* Player;
        Transform* playerTransform;
        Transform* cameraTransform;
        Transform* enemyTransform;

        Entity* camera;

        Menu(Application_Manager *manager) : Scene(manager) {
            CreateMaterials2();

            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex30_light_array/light_array.frag","SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex32_textured_material/light_array.frag","TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/fshaders/light_array.frag","TransShader");

            CGEngine::mesh_utils::Cuboid("cube",false,glm::vec3(0,0,0),glm::vec3(2.0f,0,2.0f));
            CGEngine::mesh_utils::Sphere("sphere",glm::vec2(50,50),true,glm::vec3(0,0,0),0.6f);
            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("pacman", "assets/models/chomp.obj");
            CGEngine::mesh_utils::loadOBJ("enemy", "assets/models/ghost.obj");
            CGEngine::mesh_utils::Cuboid("cuboid",false,glm::vec3(0,0,0),glm::vec3(10.0f,0,5.0f));


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
            point_light->addComponent<Transform>()->setPosition(0,1,0);
            point_light->addComponent<Light>()->setLightType(LightType::POINT);

            Entity* spot_light = createEntity("light_spot");
            spot_light->addComponent<Transform>()->setPosition(0,1,-10);
            spot_light->addComponent<Light>()->setLightType(LightType::SPOT);
            spot_light->getComponent<Light>()->setSpotAngle(1,1);
            ////////////////////////////////
//            Player = createEntity("Player");
//            Player->addComponent<Transform>();
//            Player->addComponent<Mesh_Component>()->setMeshModelName("pacman");
//            Player->addComponent<Material_Component>()->setMaterialName("house_material");
//            Player->getComponent<Transform>()->setPosition(8,5,15);
//            Player->getComponent<Transform>()->setRotation(vec3(-2, 0, 0.8));
//            Player->addComponent<RightLeftController>();

            //Systems
            addSystem<RenderSystem>();
            glm::vec3 centerPosition{0,0,0};

            play = createEntity("Play");
            play->addComponent<Transform>();
            play->addComponent<Mesh_Component>()->setMeshModelName("cube");
            play->addComponent<Material_Component>()->setMaterialName("cat_material");
            play->getComponent<Transform>()->setPosition(8,10,10);
            play->getComponent<Transform>()->setRotation(glm::vec3(0, 1.57, 0));

            Entity *Stop;
            Stop = createEntity("Stop");
            Stop->addComponent<Transform>();
            Stop->addComponent<Mesh_Component>()->setMeshModelName("cube");
            Stop->addComponent<Material_Component>()->setMaterialName("stop_material");
            Stop->getComponent<Transform>()->setPosition(14,10,10);
            // Stop->getComponent<Transform>()->setRotation(vec3(0, 0, 0));


        }

        void  start() override
        {
            glm::vec3 Position = {11,10,9};
            camera->getComponent<Transform>()->setForward(glm::vec3(0,-1,0));
            camera->getComponent<Transform>()->setPosition(Position.x, 15,Position.z);
            camera->getComponent<Transform>()->setForward(Position);
            //camera->getComponent<Transform>()->setPosition(Position.x, 15,Position.z);

        }
        void update(double deltaTime) override  {



        }
        ~Menu()
        {
            //Resource_Manager::clear();
            //mesh_utils::clearMeshes();
        }
    };
}
