#include <scene.h>
#include <shader/shader.h>
#include <camera.h>
#include <light.h>
#include <render_system.h>
#include <mesh_component.h>
#include <mesh-utils.hpp>
#include <resource_manager.h>
#include <material_component.h>
#include <material/material_assets.h>
#include "maze/maze_generator.h"
#include <right_left_controller.h>
#include <righ_left_camera_controller.h>
#include <list>
#include <enemy_movement.h>
#include <game_scene_utilities.cpp>
#include <irrKlang.h>
#include <gameover.cpp>
#include <next_level.cpp>

using namespace irrklang;

namespace CGEngine {


    class Game_Scene : public CGEngine::Scene {
    public:
        ISoundEngine *SoundEngine;

        vector<Entity *> mazeBoxs;
        vector<Entity *> mazeEnemies;
        vector<Entity *> powerUps;
        vector<Entity *> Safe;
        bool IsSafe=false;
        double SafetyTimer;
        Entity *Player;
        Entity *Door;

        Box_Collider *playerCollider;
        Transform *playerTransform;
        Transform *cameraTransform;

        Box_Collider *enemyCollider;
        Transform *enemyTransform;

        RightLeftController *movePlayerContoller;
        RightLeftCamerController *moveCamerContoller;
        bool openDoor = false;
        Entity *camera;
        glm::vec3  FinalPosition;
        Game_Scene(Application_Manager *manager, int level) : Scene(manager) {
            SoundEngine = createIrrKlangDevice();
            this-> manager = manager;
            SoundEngine->play2D("audio/HorrorPianoMusic.mp3", true);
            CreateMaterials();

            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/ex30_light_array/light_array.frag", "SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/ex32_textured_material/light_array.frag",
                                         "TexturedLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert",
                                         "assets/shaders/fshaders/light_array.frag", "TransShader");
            Resource_Manager::LoadShader("assets/shaders/ex32_textured_material/sky_transform.vert",
                                         "assets/shaders/ex32_textured_material/sky.frag", "SkyShader");

            CGEngine::mesh_utils::Cuboid("cube", true, glm::vec3(0, 0, 0), glm::vec3(2.0f, 1, 2.0f));
            CGEngine::mesh_utils::Sphere("sphere", glm::vec2(50, 50), true, glm::vec3(0, 0, 0), 0.6f);
            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("pacman", "assets/models/chomp.obj");
            CGEngine::mesh_utils::loadOBJ("enemy", "assets/models/ghost.obj");
            CGEngine::mesh_utils::loadOBJ("powerUp", "assets/models/powerUp.obj");
            CGEngine::mesh_utils::loadOBJ("cherry", "assets/models/cherry.obj");


            //Camera Entity
            camera = createEntity("Main Camera");
            cameraTransform = camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);


            Entity *Plane = createEntity("Plane");
            Plane->addComponent<Transform>()->setLocalScale(150, 1, 150);
            Plane->addComponent<Mesh_Component>()->setMeshModelName("plane");
            Plane->addComponent<Material_Component>()->setMaterialName("default_material");
            Plane->getComponent<Transform>()->setLocalPosition({0, 0, 0});





/*
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
            Player->addComponent<Material_Component>()->setMaterialName("player_material");
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
                if(availablePathes[i].start == FinalPosition||availablePathes[i].end == FinalPosition)continue;
                Enemy = createEntity("Enemy_" + to_string(i));
                Enemy->addComponent<Transform>();
                Enemy->addComponent<Mesh_Component>()->setMeshModelName("enemy");
                Enemy->addComponent<Material_Component>()->setMaterialName("ghost_material");
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
            if(level>1) {
                vector<vec3> emptyPositions = mazeGenerator.GetEmptyPositions();
                Entity *PowerUp;
                for (int i = 1; i < mazeGenerator.GetWidth(); ++i) {
                    for (int j = 1; j < mazeGenerator.GetHeight(); ++j) {
                        if (mazeGenerator.mMaze[i][j] == 0 && (rand()%(200*level))<(level*25)) {
                            PowerUp = createEntity("PowerUp_" + to_string(i) + "_" + to_string(j));
                            PowerUp->addComponent<Transform>()->setPosition(
                                    vec3(-mazeGenerator.GetWidth() / 2 + i * 2, 1,
                                         mazeGenerator.GetHeight() / 2 + j * 2));
                            PowerUp->addComponent<Mesh_Component>()->setMeshModelName("cherry");
                            PowerUp->addComponent<Material_Component>()->setMaterialName("cherry_material");
                            powerUps.push_back(PowerUp);

                        }
                    }
                }
            }else{
                vector<vec3> emptyPositions = mazeGenerator.GetEmptyPositions();
                Entity *PowerUp;
                for (int i = 1; i < mazeGenerator.GetWidth(); i+=4) {
                    for (int j = 1; j < mazeGenerator.GetHeight(); j+=4) {
                        if (mazeGenerator.mMaze[i][j] == 0) {
                            PowerUp = createEntity("PowerUp_" + to_string(i) + "_" + to_string(j));
                            PowerUp->addComponent<Transform>()->setPosition(
                                    vec3(-mazeGenerator.GetWidth() / 2 + i * 2, 1,
                                         mazeGenerator.GetHeight() / 2 + j * 2));
                            PowerUp->addComponent<Mesh_Component>()->setMeshModelName("powerUp");
                            PowerUp->addComponent<Material_Component>()->setMaterialName("powerUp_material");
                            Safe.push_back(PowerUp);

                        }
                    }
                }

            }
            ////////////////////////////////////////////////////////////////////////

            Entity* point_light = createEntity("light_point");
            point_light->addComponent<Transform>()->setPosition(FinalPosition);
            point_light->addComponent<Light>()->setLightType(LightType::POINT);
            point_light->getComponent<Light>()->setColor(glm::vec3 (1, 0.1f, 0.2f));

            Entity* point_light_2 = createEntity("light_point_2");
            point_light_2->addComponent<Transform>()->setPosition(mazeGenerator.GetStartPosition());
            point_light_2->addComponent<Light>()->setLightType(LightType::POINT);
            point_light_2->getComponent<Light>()->setColor(glm::vec3 (1, 0.1f, 0.2f));

            Entity *directional_light = createEntity("light_directional");
            directional_light->addComponent<Transform>()->setForward(glm::vec3(0,1,0));
            directional_light->addComponent<Light>()->setLightType(LightType::DIRECTIONAL);
            directional_light->getComponent<Light>()->setColor(glm::vec3(1, 1, 1));
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
            if(IsSafe==true  && deltaTime>(SafetyTimer+0.03)){
                IsSafe=false;
                Player->getComponent<Material_Component>()->setMaterialName("player_material");
            }

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
            if(IsSafe!=true){
                for (auto &enemy: mazeEnemies) {
                    bool result = CheckCollisionWithEnemy(playerTransform, enemy->getComponent<Transform>());
                    if (result) {
                        Resource_Manager::clear();
                        mesh_utils::clearMeshes();
                        Material::DestroyMaterial();
                        SoundEngine->play2D("audio/scream.mp3", false);
                        CGEngine::Scene *Game_Scene = new CGEngine::Gameover(manager);
                        manager->goToScene(Game_Scene);
                    }
                }
            }

            ////////////////////////////////////////////////////////////////////////

            //Check player collision with powerups
            int index = 0;
            for (auto &powerup: powerUps) {
                bool result = CheckCollisionWithPowerUp(playerTransform, powerup->getComponent<Transform>());
                if (result) {
                    SoundEngine->play2D("audio/cherry.mp3", false);
                    destroyEntity(powerup->name);
                    powerUps.erase (powerUps.begin()+index);
                }
                index++;
            }

            ////////////////////////////////////////////////////////////////////////
            int p=0;
            //Check player collision with safe
            for (auto &powerup: Safe) {
                bool result = CheckCollisionWithPowerUp(playerTransform, powerup->getComponent<Transform>());
                if (result) {
                    SoundEngine->play2D("audio/powerup.mp3", false);
                    destroyEntity(powerup->name);
                    Safe.erase (Safe.begin()+p);
                    Player->getComponent<Material_Component>()->setMaterialName("default_material");
                    IsSafe=true;
                    SafetyTimer=deltaTime;
                }
                p++;
            }
            ////////////////////////////////////////////////////////////////////////

            //Check opening of maze
            if( powerUps.size()==0 && (Door->getComponent<Transform>()->getPosition().z) < FinalPosition.z+2) {
                if(!openDoor)SoundEngine->play2D("audio/door.mp3", false);
                openDoor= true;
                Transform* doorTransform = Door->getComponent<Transform>();
                glm::vec3 position = doorTransform->getPosition();
                glm::vec3 forward = doorTransform->getForward();
                position -= forward * ((float)deltaTime * 1.0f);
                doorTransform->setPosition(position);
            }
            ////////////////////////////////////////////////////////////////////////

            //Check winning
            if(playerTransform->getPosition().x> FinalPosition.x + 1.1f )
            {
                Resource_Manager::clear();
                mesh_utils::clearMeshes();
                Material::DestroyMaterial();
                IsSafe=false;
                CGEngine::Scene *Game_Scene = new CGEngine::Next_Level(manager);
                manager->goToScene(Game_Scene);
            }
            ////////////////////////////////////////////////////////////////////////
        }

        void onExit() override {
            SoundEngine->drop();

        }

    };
}
