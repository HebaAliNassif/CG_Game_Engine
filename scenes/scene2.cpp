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
#include <enemy_movement.h>
namespace CGEngine
{


    class scene2 : public CGEngine::Scene {
    public:

        vector<Entity*> mazeBoxs;
        vector<Entity*> mazeEnemies;
        vector<Entity*> powerUps;
        Entity* Player;
        Entity* Enemy;
        Entity* PowerUp;

        Box_Collider* playerCollider;
        Transform* playerTransform;
        Transform* cameraTransform;

        Box_Collider* enemyCollider;
        Transform* enemyTransform;


        Entity* camera;
        scene2(Application_Manager *manager) : Scene(manager) {
            CreateMaterials();

            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex30_light_array/light_array.frag","SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex32_textured_material/light_array.frag","TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/fshaders/light_array.frag","TransShader");

            CGEngine::mesh_utils::Cuboid("cube",true,glm::vec3(0,0,0),glm::vec3(2.0f,1,2.0f));
            CGEngine::mesh_utils::Sphere("sphere",glm::vec2(50,50),true,glm::vec3(0,0,0),0.6f);
            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("pacman", "assets/models/chomp.obj");
            CGEngine::mesh_utils::loadOBJ("enemy", "assets/models/ghost.obj");
            CGEngine::mesh_utils::loadOBJ("powerUp", "assets/models/powerUp.obj");


            //Camera Entity
            camera = createEntity("Main Camera");
            cameraTransform = camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);
            camera->addComponent<RightLeftController>();

            Entity* Plane = createEntity("Plane");
            Plane->addComponent<Transform>()->setLocalScale(100,1,100);
            Plane->addComponent<Mesh_Component>()->setMeshModelName("plane");
            Plane->addComponent<Material_Component>()->setMaterialName("default_material");
            Plane->getComponent<Transform>()->setLocalPosition({0,0,0 });

            Entity* directional_light = createEntity("light_directional");
            directional_light->addComponent<Transform>();
            directional_light->addComponent<Light>()->setLightType(LightType::DIRECTIONAL);

            /*
            Entity* point_light = createEntity("light_point");
            point_light->addComponent<Transform>()->setPosition(15,1,10);
            point_light->addComponent<Light>()->setLightType(LightType::POINT);
*/
            Entity* spot_light = createEntity("light_spot");
            spot_light->addComponent<Transform>()->setPosition(10,1,15);
            spot_light->addComponent<Light>()->setLightType(LightType::SPOT);
            spot_light->getComponent<Light>()->setSpotAngle(15,20);
            //spot_light->getComponent<Light>()->setDiffuse(0.5, 0.5, 0.5);

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
            Player->addComponent<Mesh_Component>()->setMeshModelName("pacman");
            Player->addComponent<Material_Component>()->setMaterialName("house_material");
            Player->getComponent<Transform>()->setPosition(mazeGenerator.GetStartPosition().x, 0.6, mazeGenerator.GetStartPosition().z);
            Player->addComponent<RightLeftController>();
            Player->addComponent<Box_Collider>()->setMaxExtent(Player->getComponent<Transform>()->getPosition() + glm::vec3(0.6, 1, 0.6));
            Player->getComponent<Box_Collider>()->setMinExtent(Player->getComponent<Transform>()->getPosition() - glm::vec3(0.6, 1, 0.6));

            playerCollider = Player->getComponent<Box_Collider>();
            playerTransform = Player->getComponent<Transform>();
            vector<PathInWorld> availablePathes;
            vector<Path> pathesAsIndices = mazeGenerator.GetAvailablePathes();


            for (auto i : pathesAsIndices)
                availablePathes.push_back(PathInWorld(
                        UtilityFunctions::IndicesToWorldCoordiantes(i.start, mazeGenerator.GetWidth(), mazeGenerator.GetHeight()),
                        UtilityFunctions::IndicesToWorldCoordiantes(i.end, mazeGenerator.GetWidth(), mazeGenerator.GetHeight())));

            for (int i = 0; i < availablePathes.size(); ++i)
            {
                Enemy = createEntity("Enemy"+i);

                Enemy->addComponent<Transform>();
                Enemy->addComponent<Mesh_Component>()->setMeshModelName("enemy");
                Enemy->addComponent<Material_Component>()->setMaterialName("house_material");
                Enemy->addComponent<Box_Collider>()->setMaxExtent(Enemy->getComponent<Transform>()->getPosition() + glm::vec3(1, 1, 1));
                Enemy->getComponent<Box_Collider>()->setMinExtent(Enemy->getComponent<Transform>()->getPosition() - glm::vec3(1, 1, 1));
                Enemy->getComponent<Transform>()->setPosition(availablePathes[i].start.x, mazeGenerator.GetStartPosition().y, availablePathes[i].start.z);

                Enemy->addComponent<EnemyMovement>()->setIsHorizontal((availablePathes[i].start.z - availablePathes[i].end.z) == 0);
                Enemy->getComponent<EnemyMovement>()->setStart(availablePathes[i].start);
                Enemy->getComponent<EnemyMovement>()->setEnd(availablePathes[i].end);
                mazeEnemies.push_back(Enemy);
            }

            vector<vec3> emptyPositions = mazeGenerator.GetEmptyPositions();
            for (int i = 0; i < emptyPositions.size(); ++i) {
                if (rand() % 100 < 20) {
                    PowerUp = createEntity("PowerUp" + i);

                    PowerUp->addComponent<Transform>();
                    PowerUp->addComponent<Mesh_Component>()->setMeshModelName("powerUp");
                    PowerUp->addComponent<Material_Component>()->setMaterialName("house_material");
                    PowerUp->addComponent<Box_Collider>()->setMaxExtent(
                            Enemy->getComponent<Transform>()->getPosition() + glm::vec3(1, 1, 1));
                    PowerUp->getComponent<Box_Collider>()->setMinExtent(
                            Enemy->getComponent<Transform>()->getPosition() - glm::vec3(1, 1, 1));
                    PowerUp->getComponent<Transform>()->setPosition(emptyPositions[i]);

                    powerUps.push_back(PowerUp);
                }
            }


        }
        RightLeftController* movePlayerContoller ;
        RightLeftCamerController* moveCamerContoller;
        void  start() override
        {
            glm::vec3 Position = playerTransform->getPosition();
            camera->getComponent<Transform>()->setForward(glm::vec3(0,-1,0));
            camera->getComponent<Transform>()->setPosition(Position.x, 15,Position.z);
            camera->getComponent<Transform>()->setForward(Position);
            camera->getComponent<Transform>()->setPosition(Position.x, 15,Position.z);
            camera->addComponent<RightLeftCamerController>();
            movePlayerContoller = Player->getComponent<RightLeftController>();
            moveCamerContoller = camera->getComponent<RightLeftCamerController>();

        }
        glm::vec3  position_sensitivity = {5.0f, 5.0f, 5.0f};
        bool Collide(glm::vec3 point)
        {
            for (auto &entity: mazeBoxs)
            {
                Box_Collider* box = entity->getComponent<Box_Collider>();
                glm::vec3 distance1 = box->getMinExtent() - playerCollider->getMaxExtent();
                glm::vec3 distance2 = playerCollider->getMinExtent() - box->getMaxExtent();
                glm::vec3 distance = glm::vec3(glm::max(distance1.x, distance2.x), glm::max(distance1.y, distance2.y), glm::max(distance1.z, distance2.z));
                float maxDistance = glm::max(distance.x, glm::max(distance.y, distance.z));
                if (maxDistance < 0) {
                    return true;
                }
            }
            return false;
        }
        void updateEnemyColliders()
        {
            for (auto &enemy: mazeEnemies)
            {
                enemy->getComponent<Box_Collider>()->setMinExtent( enemy->getComponent<Transform>()->getPosition() - vec3(0.5f, 0.5f, 0.5f));
                enemy->getComponent<Box_Collider>()->setMaxExtent(enemy->getComponent<Transform>()->getPosition() + vec3(0.5f, 0.5f, 0.5f));
            }
        }

        enum Direction {
            Front,
            RIGHT,
            Back,
            LEFT
        };
        typedef std::tuple<bool, Direction, glm::vec3> Collision;

        Direction VectorDirection(glm::vec3 target)
        {
            glm::vec3 compass[] = {
                    glm::vec3(0.0f, 0.0f, -1.0f),	// front
                    glm::vec3(1.0f, 0.0f, 0.0f),	// right
                    glm::vec3(0.0f, 0.0f, 1.0f),	// back
                    glm::vec3(-1.0f, 0.0f, 0.0f)	// left
            };
            float max = 0.0f;
            unsigned int best_match = -1;
            for (unsigned int i = 0; i < 4; i++)
            {
                float dot_product = glm::dot(glm::normalize(target), compass[i]);
                if (dot_product > max)
                {
                    max = dot_product;
                    best_match = i;
                }
            }
            return (Direction)best_match;
        }
        Collision  CheckCollision(Transform* one, Transform *two) // AABB - Circle collision
        {
            // get center point circle first
            glm::vec3 center(one->getPosition().x, 0.6f, one->getPosition().z);

            // calculate AABB info (center, half-extents)
            glm::vec3 aabb_half_extents(2/ 2.0f, 0.5f,2 / 2.0f);
            glm::vec3 aabb_center(two->getPosition());

            // get difference vector between both centers
            glm::vec3 difference = center - aabb_center;
            glm::vec3 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);

            // add clamped value to AABB_center and we get the value of box closest to circle
            glm::vec3 closest = aabb_center + clamped;

            // retrieve vector between center circle and closest point AABB and check if length <= radius
            difference = closest - center;
           // return glm::length(difference) < 0.65f;
            if (glm::length(difference) <= 0.7f)
                return std::make_tuple(true, VectorDirection(difference), difference);
            else
                return std::make_tuple(false, Front, glm::vec3(0.0f, 0.0f, 0.0f));
        }

        void update(double deltaTime) override  {
            playerCollider->setMinExtent(playerTransform->getPosition() - vec3(0.5f, 0.5f, 0.5f));
            playerCollider->setMaxExtent(playerTransform->getPosition() + vec3(0.5f, 0.5f, 0.5f));
            //std::cout<<"Center: "<<playerTransform->getPosition().x<<"\t"<<playerTransform->getPosition().y<<"\t"<<playerTransform->getPosition().z<<"\n";
            bool flag_hit = false;
            for (auto &entity: mazeBoxs) {
                Box_Collider *box = entity->getComponent<Box_Collider>();
                glm::vec3 boxPosition = entity->getComponent<Transform>()->getPosition();
                glm::vec3 playerPosition = playerTransform->getPosition();
                //std::cout<<playerTransform->getRight().x<<"\t"<<playerTransform->getRight().y<<"\t"<<playerTransform->getRight().z<<"\n";
                //HitInfo hit = Player->getComponent<Box_Collider>()->onCollision(box);
                Collision result = CheckCollision(playerTransform, entity->getComponent<Transform>());
                if (std::get<0>(result)) {
                    flag_hit =  true;
                    //std::cout << std::get<1>(result) << "\n";
                    if(std::get<1>(result) == 0)
                    {
                        movePlayerContoller->freeze_movement_up = true;
                        moveCamerContoller->freeze_movement_up = true;
                    }
                    else if(std::get<1>(result) == 1)
                    {
                        movePlayerContoller->freeze_movement_right = true;
                        moveCamerContoller->freeze_movement_right = true;
                    }
                    else if(std::get<1>(result) == 2)
                    {
                        movePlayerContoller->freeze_movement_down = true;
                        moveCamerContoller->freeze_movement_down = true;
                    }
                    else if(std::get<1>(result) == 3)
                    {
                        movePlayerContoller->freeze_movement_left = true;
                        moveCamerContoller->freeze_movement_left = true;
                    }
                    //std::cout << std::get<1>(result) << "\n";
                }

                /*if (hit.isColliding)
                {
                    flag_hit =  true;
                    if(  boxPosition.z <= playerPosition.z && !moveCamerContoller->freeze_movement_up && !movePlayerContoller->freeze_movement_down)
                    {
                        movePlayerContoller->freeze_movement_up = true;
                        moveCamerContoller->freeze_movement_up = true;
                    }
                    if(boxPosition.x > playerPosition.x && !movePlayerContoller->freeze_movement_up)
                    {
                        movePlayerContoller->freeze_movement_down = true;
                        moveCamerContoller->freeze_movement_down = true;
                    }
                    if(boxPosition.x >= playerPosition.x && !movePlayerContoller->freeze_movement_right&& !movePlayerContoller->freeze_movement_left)
                    {
                        movePlayerContoller->freeze_movement_right = true;
                        moveCamerContoller->freeze_movement_right = true;
                    }
                    if(boxPosition.x <= playerPosition.x && !movePlayerContoller->freeze_movement_left&& !movePlayerContoller->freeze_movement_right)
                    {
                        movePlayerContoller->freeze_movement_left = true;
                        moveCamerContoller->freeze_movement_left = true;
                    }
                    playerCollider->setMinExtent( playerTransform->getPosition() - vec3(0.5f, 0.5f, 0.5f));
                    playerCollider->setMaxExtent(playerTransform->getPosition() + vec3(0.5f, 0.5f, 0.5f));
                }*/
            }
            if(!flag_hit)
            {
                movePlayerContoller->resetcontrollers();
                moveCamerContoller->resetcontrollers();
            }
            updateEnemyColliders();

            for (auto &enemy: mazeEnemies) {
                Box_Collider* box = enemy->getComponent<Box_Collider>();
                HitInfo hit = Player->getComponent<Box_Collider>()->onCollision(box);
                if (hit.isColliding) {
                    cout<<"Game Over\n";
                }
            }
        }

        void onExit() override
        {
            //getEntity("Main Camera")->getComponent<FlyController>()->release();
            Resource_Manager::clear();
            mesh_utils::clearMeshes();
        }

    };
}
