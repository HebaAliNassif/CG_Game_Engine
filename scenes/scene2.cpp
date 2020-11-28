#include <scene.h>
#include <shader.h>
#include "iostream"
#include <mesh.h>
#include <camera-controller.h>
#include <mesh-utils.hpp>
#include <application_manager.h>
#include <camera.h>
#include "renderSystem.h"

namespace CGEngine
{
    class scene2 : public CGEngine::Scene {
    public:
        Shader program;
        Mesh model;
        std::vector<Transform> objects;
        renderSystem Render;
        scene2()
        {
            program = Shader::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");

            CGEngine::mesh_utils::Cuboid(model, true);

            Entity* shape = createEntity("Main Camera");
            shape->addComponent<Transform>();
            shape->addComponent<Camera>();
            addSystem<CameraController>();
            shape->addComponent<MeshC>();
            shape->getComponent<Camera>()->setEyePosition({10, 10, 10});
            shape->getComponent<Camera>()->setTarget({0, 0, 0});
        }
        void  start(Application_Manager* manager) override
        {

            int width, height;
            glfwGetFramebufferSize(manager->getWindow(), &width, &height);

            Entity* E = this->getEntity("Main Camera");
             E->getComponent<MeshC>()->setmesh(model);
             E->getComponent<MeshC>()->setProgram(program);
             E->getComponent<Transform>()->setLocalPosition({0,-1,0});
             E->getComponent<Transform>()->setLocalRotation({0,0,0,0});
             E->getComponent<Transform>()->setLocalScale({7,2,7});
             E->getComponent<Camera>()->setUp({0,1,0});
             E->getComponent<Camera>()->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);
            getSystem<CameraController>()->initialize(manager, E->getComponent<Camera>());

        }
        void update(double deltaTime) override  {
            Entity* E = this->getEntity("Main Camera");
              vector<Entity*> Entities;

            Entities.push_back(E);
            Render.renderAll(Entities);
        }
        ~scene2()
        {
            //program.destroy();
            //model.destroy();
            //camera_controller.release();
        }
    };
}
