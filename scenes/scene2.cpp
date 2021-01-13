#include <scene.h>
#include <shader/shader.h>
#include <glm/gtc/noise.hpp>
#include <mesh.h>
#include <systems/fly-controller.h>
#include <application_manager.h>
#include <camera.h>
#include <light.h>
#include <render_system.h>
#include <mesh_component.h>
#include <shape_script.cpp>
#include <mesh-utils.hpp>
#include <resource_manager.h>
#include <material_component.h>
#include <material/material_assets.h>
#include "maze/maze_generator.h"
#include <right_left_controller.h>
#include <righ_left_camera_controller.h>
#include <list>
#include <box_collider.h>
namespace CGEngine
{


    class scene2 : public CGEngine::Scene {
    public:

        vector<Entity*> mazeBoxs;
        Entity* Player;
        Box_Collider* playerCollider;
        Transform* playerTransform;
        Entity* camera;
        scene2()
        {
            CreateMaterials();

            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex30_light_array/light_array.frag","SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex32_textured_material/light_array.frag","TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/fshaders/light_array.frag","TransShader");

            CGEngine::mesh_utils::Cuboid("cube",true,glm::vec3(0,0,0),glm::vec3(2.0f,1,2.0f));
            CGEngine::mesh_utils::Sphere("sphere",glm::vec2(50,50),true,glm::vec3(0,0,0),0.8f);
            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("cat", "assets/models/Cat.obj");

            //Camera Entity
            camera = createEntity("Main Camera");
            camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);
            //camera->addComponent<RightLeftController>();

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


            //Systems
            addSystem<RenderSystem>();

            int seed = rand();

            MazeGenerator mazeGenerator(20, 10, seed, 35);
            mazeGenerator.GenerateMap();

            int boxesCount = 0;

            glm::vec3 centerPosition{0,0,0};
            Entity *tmpBox = NULL;
            for (int i = 0; i < mazeGenerator.GetWidth(); ++i)
            {
                for (int j = 0; j < mazeGenerator.GetHeight(); ++j)
                {
                    if (mazeGenerator.mMaze[i][j] == 1)
                    {
                        boxesCount++;
                        tmpBox = createEntity("Box_"+to_string(i)+"_"+ to_string(j));
                        tmpBox->addComponent<Transform>()->setPosition(vec3(-mazeGenerator.GetWidth() / 2 + i * 2, 1, mazeGenerator.GetHeight() / 2 + j * 2));
                        tmpBox->getComponent<Transform>()->setRotation( vec3(0, 0, 0));
                        tmpBox->getComponent<Transform>()->setLocalScale(vec3(1, 1,1));
                        tmpBox->addComponent<Mesh_Component>()->setMeshModelName("cube");
                        tmpBox->addComponent<Material_Component>()->setMaterialName("default_material");
                        tmpBox->addComponent<Box_Collider>()->setMaxExtent(tmpBox->getComponent<Transform>()->getPosition() + glm::vec3(1, 1, 1));
                        tmpBox->getComponent<Box_Collider>()->setMinExtent(tmpBox->getComponent<Transform>()->getPosition() - glm::vec3(1, 1, 1));
                        mazeBoxs.push_back(tmpBox);
                        centerPosition += tmpBox->getComponent<Transform>()->getPosition();

                    }
                }
            }
            centerPosition /= boxesCount;


            Player = createEntity("Player");
            Player->addComponent<Transform>();
            Player->addComponent<Mesh_Component>()->setMeshModelName("sphere");
            Player->addComponent<Material_Component>()->setMaterialName("default_material");
            Player->getComponent<Transform>()->setPosition(mazeGenerator.GetStartPosition());
            Player->addComponent<RightLeftController>();
            Player->addComponent<Box_Collider>()->setMaxExtent(Player->getComponent<Transform>()->getPosition() + glm::vec3(1, 1, 1));
            Player->getComponent<Box_Collider>()->setMinExtent(Player->getComponent<Transform>()->getPosition() - glm::vec3(1, 1, 1));

            playerCollider = Player->getComponent<Box_Collider>();
            playerTransform = Player->getComponent<Transform>();




        }
        void  start() override
        {
            glm::vec3 Position = playerTransform->getPosition();
            camera->getComponent<Transform>()->setForward(glm::vec3(0,-1,0));
            camera->getComponent<Transform>()->setPosition(Position.x, 15,Position.z);
            camera->getComponent<Transform>()->setForward(Position);
            camera->getComponent<Transform>()->setPosition(Position.x, 15,Position.z);
            camera->addComponent<RightLeftCamerController>();
            //std::cout<<"start\t"<<Position.x<<"\t"<<Position.y<<"\t"<<Position.z<<"\n";
            //std::cout<<"camera start\t"<<camera->getComponent<Transform>()->getPosition().x<<"\t"<<camera->getComponent<Transform>()->getPosition().y<<"\t"<<camera->getComponent<Transform>()->getPosition().z<<"\n";
            //std::cout<<"camera forward start\t"<<camera->getComponent<Transform>()->getForward().x<<"\t"<<camera->getComponent<Transform>()->getForward().y<<"\t"<<camera->getComponent<Transform>()->getForward().z<<"\n";


        }
        void update(double deltaTime) override  {
            //glm::vec3 centerPosition = playerTransform->getPosition();
            //std::cout<<"update\t"<<centerPosition.x<<"\t"<<centerPosition.y<<"\t"<<centerPosition.z<<"\n";
            //std::cout<<"camera update\t"<<camera->getComponent<Transform>()->getPosition().x<<"\t"<<camera->getComponent<Transform>()->getPosition().y<<"\t"<<camera->getComponent<Transform>()->getPosition().z<<"\n";
            //std::cout<<"camera forward update\t"<<camera->getComponent<Transform>()->getForward().x<<"\t"<<camera->getComponent<Transform>()->getForward().y<<"\t"<<camera->getComponent<Transform>()->getForward().z<<"\n";

            //camera->getComponent<Transform>()->setForward(centerPosition);
            //camera->getComponent<Transform>()->setPosition(centerPosition.x, 15,centerPosition.z);
/*
            playerCollider->setMinExtent( playerTransform->getPosition() - vec3(0.5f, 0.5f, 0.5f));
            playerCollider->setMaxExtent(playerTransform->getPosition() + vec3(0.5f, 0.5f, 0.5f));

            for (auto &entity: mazeBoxs)
            {
                Box_Collider* box = entity->getComponent<Box_Collider>();
                glm::vec3 boxPosition = entity->getComponent<Transform>()->getPosition();
                glm::vec3 playerPosition = playerTransform->getPosition();
                HitInfo hit = Player->getComponent<Box_Collider>()->onCollision(box);
                RightLeftController* movePlayerContoller = Player->getComponent<RightLeftController>();
                if (hit.isColliding == true)
                {
                    //std::cout<<"Box\t"<<entity->getComponent<Transform>()->getPosition().x<<"\t"<<entity->getComponent<Transform>()->getPosition().y<<"\t"<<entity->getComponent<Transform>()->getPosition().z<<"\n";
                    //std::cout<<"Player\t"<<Player->getComponent<Transform>()->getPosition().x<<"\t"<<Player->getComponent<Transform>()->getPosition().y<<"\t"<<Player->getComponent<Transform>()->getPosition().z<<"\n";
                    if(boxPosition.z < playerPosition.z && !movePlayerContoller->freeze_movement_left)
                    {
                        movePlayerContoller->freeze_movement_right = true;
                    }
                    if(boxPosition.z > playerPosition.z && !movePlayerContoller->freeze_movement_right)
                    {
                        movePlayerContoller->freeze_movement_left = true;
                    }
                    if(boxPosition.x < playerPosition.x && !movePlayerContoller->freeze_movement_down)
                    {
                        movePlayerContoller->freeze_movement_up = true;
                    }
                    if(boxPosition.x > playerPosition.x && !movePlayerContoller->freeze_movement_up)
                    {
                        movePlayerContoller->freeze_movement_down = true;
                    }
                    playerCollider->setMinExtent( playerTransform->getPosition() - vec3(0.5f, 0.5f, 0.5f));
                    playerCollider->setMaxExtent(playerTransform->getPosition() + vec3(0.5f, 0.5f, 0.5f));
                }
            }*/

        }

        void onExit() override
        {
            //getEntity("Main Camera")->getComponent<FlyController>()->release();
            Resource_Manager::clear();
            mesh_utils::clearMeshes();
        }

    };
}
