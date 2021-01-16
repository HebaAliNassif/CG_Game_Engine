#include <scene.h>
#include <shader/shader.h>
#include <glm/gtc/noise.hpp>
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
#include <game_scene_utilities.cpp>

namespace CGEngine {


    class Game_Scene : public CGEngine::Scene {
    public:

        vector<Entity *> mazeBoxs;
        vector<Entity *> mazeEnemies;
        vector<Entity *> powerUps;
        Entity *Player;
        Entity *Door;

        Box_Collider *playerCollider;
        Transform *playerTransform;
        Transform *cameraTransform;

        Box_Collider *enemyCollider;
        Transform *enemyTransform;

        RightLeftController *movePlayerContoller;
        RightLeftCamerController *moveCamerContoller;

        Entity *camera;
        glm::vec3  FinalPosition;
        Game_Scene(Application_Manager *manager) : Scene(manager) {
            CreateMaterials();

            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/ex30_light_array/light_array.frag", "SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/ex32_textured_material/light_array.frag",
                                         "TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/fshaders/light_array.frag", "TransShader");

            CGEngine::mesh_utils::Cuboid("cube", true, glm::vec3(0, 0, 0), glm::vec3(2.0f, 1, 2.0f));
            CGEngine::mesh_utils::Sphere("sphere", glm::vec2(50, 50), true, glm::vec3(0, 0, 0), 0.6f);
            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("pacman", "assets/models/chomp.obj");
            CGEngine::mesh_utils::loadOBJ("enemy", "assets/models/ghost.obj");
            CGEngine::mesh_utils::loadOBJ("powerUp", "assets/models/powerUp.obj");


            //Camera Entity
            camera = createEntity("Main Camera");
            cameraTransform = camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);


            Entity *Plane = createEntity("Plane");
            Plane->addComponent<Transform>()->setLocalScale(100, 1, 100);
            Plane->addComponent<Mesh_Component>()->setMeshModelName("plane");
            Plane->addComponent<Material_Component>()->setMaterialName("default_material");
            Plane->getComponent<Transform>()->setLocalPosition({0, 0, 0});

            Entity *directional_light = createEntity("light_directional");
            directional_light->addComponent<Transform>();
            directional_light->addComponent<Light>()->setLightType(LightType::DIRECTIONAL);

            /*
            Entity* point_light = createEntity("light_point");
            point_light->addComponent<Transform>()->setPosition(15,1,10);
            point_light->addComponent<Light>()->setLightType(LightType::POINT);

            Entity* spot_light = createEntity("light_spot");
            spot_light->addComponent<Transform>()->setPosition(10,1,15);
            spot_light->addComponent<Light>()->setLightType(LightType::SPOT);
            spot_light->getComponent<Light>()->setSpotAngle(15,20);
            //spot_light->getComponent<Light>()->setDiffuse(0.5, 0.5, 0.5);
*/
            //Systems
            addSystem<RenderSystem>();
            ////////////////////////////////////////////////////////////////////////

            //Generating the maze
            int seed = rand();
            MazeGenerator mazeGenerator(20, 10, seed, 35);
            mazeGenerator.GenerateMap();
            int boxesCount = 0;
            glm::vec3 centerPosition{0, 0, 0};
            Entity *tmpBox = NULL;
            for (int i = 0; i < mazeGenerator.GetWidth(); ++i) {
                for (int j = 0; j < mazeGenerator.GetHeight(); ++j) {
                    if (mazeGenerator.mMaze[i][j] == 1) {
                        boxesCount++;
                        tmpBox = createEntity("Box_" + to_string(i) + "_" + to_string(j));
                        tmpBox->addComponent<Transform>()->setPosition(
                                vec3(-mazeGenerator.GetWidth() / 2 + i * 2, 1, mazeGenerator.GetHeight() / 2 + j * 2));
                        tmpBox->getComponent<Transform>()->setRotation(vec3(0, 0, 0));
                        tmpBox->getComponent<Transform>()->setLocalScale(vec3(1, 1, 1));
                        tmpBox->addComponent<Mesh_Component>()->setMeshModelName("cube");
                        tmpBox->addComponent<Material_Component>()->setMaterialName("default_material");
                        mazeBoxs.push_back(tmpBox);
                        centerPosition += tmpBox->getComponent<Transform>()->getPosition();

                    }
                }
            }
            centerPosition /= boxesCount;
            FinalPosition = mazeGenerator.GetFinishPosition();
            //Generating the doors
            Door = createEntity("Door_1");
            Door->addComponent<Transform>()->setPosition(
                    vec3(mazeGenerator.GetStartPosition().x-2, 1, mazeGenerator.GetStartPosition().z));
            Door->addComponent<Mesh_Component>()->setMeshModelName("cube");
            Door->addComponent<Material_Component>()->setMaterialName("default_material");
            mazeBoxs.push_back(Door);
            Door = createEntity("Door_2");
            Door->addComponent<Transform>()->setPosition(
                    vec3(mazeGenerator.GetFinishPosition().x+2, 1, mazeGenerator.GetFinishPosition().z));
            Door->addComponent<Mesh_Component>()->setMeshModelName("cube");
            Door->addComponent<Material_Component>()->setMaterialName("default_material");
            mazeBoxs.push_back(Door);
            ////////////////////////////////////////////////////////////////////////

            //Creating the player
            Player = createEntity("Player");
            Player->addComponent<Transform>()->setEulerAngles(0, 90, 0);
            Player->addComponent<Mesh_Component>()->setMeshModelName("pacman");
            Player->addComponent<Material_Component>()->setMaterialName("house_material");
            Player->getComponent<Transform>()->setPosition(mazeGenerator.GetStartPosition().x, 0.6,
                                                           mazeGenerator.GetStartPosition().z);
            Player->addComponent<RightLeftController>();
            playerTransform = Player->getComponent<Transform>();
            ////////////////////////////////////////////////////////////////////////

            //Creating enemies
            vector<PathInWorld> availablePathes;
            vector<Path> pathesAsIndices = mazeGenerator.GetAvailablePathes();
            for (auto i : pathesAsIndices) {
                availablePathes.push_back(PathInWorld(
                        UtilityFunctions::IndicesToWorldCoordiantes(i.start, mazeGenerator.GetWidth(),
                                                                    mazeGenerator.GetHeight()),
                        UtilityFunctions::IndicesToWorldCoordiantes(i.end, mazeGenerator.GetWidth(),
                                                                    mazeGenerator.GetHeight())));
            }
            Entity *Enemy;
            for (int i = 0; i < availablePathes.size(); ++i) {
                Enemy = createEntity("Enemy_" + to_string(i));
                Enemy->addComponent<Transform>();
                Enemy->addComponent<Mesh_Component>()->setMeshModelName("enemy");
                Enemy->addComponent<Material_Component>()->setMaterialName("house_material");
                Enemy->addComponent<Box_Collider>()->setMaxExtent(
                        Enemy->getComponent<Transform>()->getPosition() + glm::vec3(1, 1, 1));
                Enemy->getComponent<Box_Collider>()->setMinExtent(
                        Enemy->getComponent<Transform>()->getPosition() - glm::vec3(1, 1, 1));
                Enemy->getComponent<Transform>()->setPosition(availablePathes[i].start.x,
                                                              mazeGenerator.GetStartPosition().y,
                                                              availablePathes[i].start.z);

                Enemy->addComponent<EnemyMovement>()->setIsHorizontal(
                        (availablePathes[i].start.z - availablePathes[i].end.z) == 0);
                Enemy->getComponent<EnemyMovement>()->setStart(availablePathes[i].start);
                Enemy->getComponent<EnemyMovement>()->setEnd(availablePathes[i].end);
                mazeEnemies.push_back(Enemy);
            }
            ////////////////////////////////////////////////////////////////////////

            //Creating poweups
            vector<vec3> emptyPositions = mazeGenerator.GetEmptyPositions();
            Entity *PowerUp;
            for (int i = 1; i < mazeGenerator.GetWidth(); ++i) {
                for (int j = 1; j < mazeGenerator.GetHeight(); ++j) {
                    if (mazeGenerator.mMaze[i][j] == 0) {
                        PowerUp = createEntity("PowerUp_" + to_string(i) + "_" + to_string(j));
                        PowerUp->addComponent<Transform>()->setPosition(
                                vec3(-mazeGenerator.GetWidth() / 2 + i * 2, 1, mazeGenerator.GetHeight() / 2 + j * 2));
                        PowerUp->addComponent<Mesh_Component>()->setMeshModelName("powerUp");
                        PowerUp->addComponent<Material_Component>()->setMaterialName("house_material");
                        powerUps.push_back(PowerUp);

                    }
                }
            }
            ////////////////////////////////////////////////////////////////////////

        }

        void start() override {
            glm::vec3 Position = playerTransform->getPosition();
            camera->getComponent<Transform>()->setForward(glm::vec3(0, -1, 0));
            camera->getComponent<Transform>()->setPosition(Position.x, 15, Position.z);
            camera->getComponent<Transform>()->setForward(Position);
            camera->getComponent<Transform>()->setPosition(Position.x, 15, Position.z);
            camera->addComponent<RightLeftCamerController>();
            movePlayerContoller = Player->getComponent<RightLeftController>();
            moveCamerContoller = camera->getComponent<RightLeftCamerController>();

        }

        void update(double deltaTime) override {

            //Check player collision with maze
            bool flag_hit = false;
            for (auto &entity: mazeBoxs) {
                glm::vec3 boxPosition = entity->getComponent<Transform>()->getPosition();
                glm::vec3 playerPosition = playerTransform->getPosition();
                Collision result = CheckCollision(playerTransform, entity->getComponent<Transform>());
                if (std::get<0>(result)) {
                    flag_hit = true;
                    if (std::get<1>(result) == 0) {
                        movePlayerContoller->freeze_movement_up = true;
                        moveCamerContoller->freeze_movement_up = true;
                    } else if (std::get<1>(result) == 1) {
                        movePlayerContoller->freeze_movement_right = true;
                        moveCamerContoller->freeze_movement_right = true;
                    } else if (std::get<1>(result) == 2) {
                        movePlayerContoller->freeze_movement_down = true;
                        moveCamerContoller->freeze_movement_down = true;
                    } else if (std::get<1>(result) == 3) {
                        movePlayerContoller->freeze_movement_left = true;
                        moveCamerContoller->freeze_movement_left = true;
                    }
                }
            }
            if (!flag_hit) {
                movePlayerContoller->resetcontrollers();
                moveCamerContoller->resetcontrollers();
            }
            ////////////////////////////////////////////////////////////////////////

            //Check player collision with enemies
            for (auto &enemy: mazeEnemies) {
                bool result = CheckCollisionWithEnemy(playerTransform, enemy->getComponent<Transform>());
                if (result) {
                    cout << "Game Over\n";
                }
            }
            ////////////////////////////////////////////////////////////////////////

            //Check player collision with powerups
            int index = 0;
            for (auto &powerup: powerUps) {
                bool result = CheckCollisionWithPowerUp(playerTransform, powerup->getComponent<Transform>());
                if (result) {
                    destroyEntity(powerup->name);
                    powerUps.erase (powerUps.begin()+index);
                }
                index++;
            }
            ////////////////////////////////////////////////////////////////////////

            //Check opening of maze
            if(powerUps.size()==0 && (Door->getComponent<Transform>()->getPosition().z) < FinalPosition.z+2) {
                Transform* doorTransform = Door->getComponent<Transform>();
                glm::vec3 position = doorTransform->getPosition();
                glm::vec3 forward = doorTransform->getForward();
                position -= forward * ((float)deltaTime * 2);
                doorTransform->setPosition(position);
            }
            ////////////////////////////////////////////////////////////////////////

            //Check winning
            if(playerTransform->getPosition().x> FinalPosition.x + 2.1f )
            {
                std::cout<<"Win\n";
            }
            ////////////////////////////////////////////////////////////////////////
        }

        void onExit() override {
            //getEntity("Main Camera")->getComponent<FlyController>()->release();
            Resource_Manager::clear();
            mesh_utils::clearMeshes();
        }

    };
}
