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
            addSystem<CameraController>();

            shape->getComponent<Camera>()->setEyePosition({10, 10, 10});
            shape->getComponent<Camera>()->setTarget({0, 0, 0});

        }
        void  start(Application_Manager* manager) override
        {
            program = Shader::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");
            CGEngine::mesh_utils::Cuboid(model, true);

            int width, height;
            glfwGetFramebufferSize(manager->getWindow(), &width, &height);

            Entity* E = this->getEntity("Main Camera");

            E->getComponent<Camera>()->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);
            getSystem<CameraController>()->initialize(manager, E->getComponent<Camera>());

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
                glm::mat4 mat= object.to_mat4();
                program.set("transform", E->getComponent<Camera>()->getVPMatrix() * mat);
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
