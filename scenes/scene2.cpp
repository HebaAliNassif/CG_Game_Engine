#include <scene.h>
#include <shader.h>
#include "iostream"
#include <mesh.h>
#include <camera-controller.h>
#include <mesh-utils.hpp>
#include <application_manager.h>
#include <camera.h>

namespace CGEngine
{
    class scene2 : public CGEngine::Scene {
    public:
        Shader program;
        Mesh model;
        std::vector<Transform> objects;

        scene2()
        {
            Entity* shape = createEntity("Main Camera");
            shape->addComponent<Transform>();
            shape->addComponent<Camera>();
            shape->getComponent<Camera>()->setEyePosition({10, 10, 10});
            shape->getComponent<Camera>()->setTarget({0, 0, 0});
            addSystem<CameraController>();
        }
        void  start(Application_Manager* manager) override
        {
            program = Shader::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");
            CGEngine::mesh_utils::Cuboid(model, true);
            objects.push_back({ {0,-1,0}, {0,0,0,0}, {7,2,7} });
            objects.push_back({ {-2,1,-2}, {0,0,0,0}, {2,2,2} });
            objects.push_back({ {2,1,-2}, {0,0,0,0}, {2,2,2} });
            objects.push_back({ {-2,1,2}, {0,0,0,0}, {2,2,2} });
            objects.push_back({ {2,1,2}, {0,0,0,0}, {2,2,2} });
            glUseProgram(program.programID);

        }
        void update(double deltaTime) override  {
            Entity* E = this->getEntity("Main Camera");
            program.set("tint", glm::vec4(1,1,1,1));

            for(const auto& object : objects) {
                program.set("transform", E->getComponent<Camera>()->getVPMatrix() * glm::transpose(object.getLocalToWorldMatrix()));
                model.draw();
            }
        }
        ~scene2()
        {
            program.destroy();
            model.destroy();
            //camera_controller.release();
        }
    };
}
