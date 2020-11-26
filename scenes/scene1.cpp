#include <scene.h>
#include <shader.h>
#include <camera.h>
#include "iostream"
#include <mesh.h>
#include <camera-controller.h>
#include <mesh-utils.hpp>
#include <application_manager.h>
namespace CGEngine
{
    class scene1 : public CGEngine::Scene {
    public:
        Shader program;
        Mesh model;
        std::vector<Transform> objects;

        scene1()
        {
            Entity* shape = createEntity("shape");
            shape->addComponent<Transform>();
            shape->addComponent<Camera>();
            shape->addComponent<CameraController>();
        }
        void  start(Application_Manager* manager) override
        {
            program = Shader::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");
            CGEngine::mesh_utils::Cuboid(model, true);

            objects.push_back({ {0,-1,0}, {0,0,0,0}, {7,2,7} });
            int width, height;
            glfwGetFramebufferSize(manager->getWindow(), &width, &height);

            Entity* E = this->getEntity("shape");

            E->getComponent<Camera>()->setEyePosition({10, 10, 10});

            E->getComponent<Camera>()->setTarget({0, 0, 0});
            E->getComponent<Camera>()->setUp({0, 1, 0});
            E->getComponent<Camera>()->setupPerspective(glm::pi<float>()/2, static_cast<float>(width)/height, 0.1f, 100.0f);

            E->getComponent<CameraController>()->initialize(manager, E->getComponent<Camera>());
            glClearColor(0, 0, 0, 0);

        }
        void update(double deltaTime) override  {

            Entity* E = this->getEntity("shape");
            E->getComponent<CameraController>()->update(deltaTime);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glUseProgram(program.programID);

            program.set("tint", glm::vec4(1,1,1,1));

            for(const auto& object : objects) {
                glm::mat4 mat=object.to_mat4();
                program.set("transform", E->getComponent<Camera>()->getVPMatrix() * mat);
                model.draw();
            }

            //NOTE: Remember to reset the color mask such that ImGUI can draw
            glColorMask(true, true, true, true);
        }
        void onExit() override
        {
            program.destroy();
            model.destroy();
            //camera_controller.release();
            //At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame.
            glLoadIdentity();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        ~scene1()
        {
        }
    };
}
