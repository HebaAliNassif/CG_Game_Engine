#include <scene.h>
#include <shader.h>
#include "iostream"
#include <mesh.h>
#include <systems/camera-controller.h>
#include <mesh-utils.hpp>
#include <application_manager.h>
#include <camera.h>
#include <render_system.h>
#include <MeshC.h>
namespace CGEngine
{
    class scene2 : public CGEngine::Scene {
    public:
        Shader program;
        Mesh model;
        std::vector<Transform> objects;
        scene2()
        {
            program = Shader::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");
            CGEngine::mesh_utils::Cuboid(model, true);

            //Camera Entity
            Entity* camera = createEntity("Main Camera");
            camera->addComponent<Transform>();
            camera->addComponent<Camera>();
            camera->getComponent<Camera>()->setEyePosition({10, 10, 10});
            camera->getComponent<Camera>()->setTarget({0, 0, 0});



            //Shape Entity
            Entity* shape = createEntity("Shape");
            shape->addComponent<Transform>();
            shape->addComponent<MeshC>();
            shape->getComponent<MeshC>()->setmesh(model);
            shape->getComponent<MeshC>()->setProgram(program);

            //Systems
            addSystem<CameraController>();
            addSystem<RenderSystem>();
        }
        void  start(Application_Manager* manager) override
        {
        }
        void update(double deltaTime) override  {

        }
        ~scene2()
        {
            //program.destroy();
            //model.destroy();
            //camera_controller.release();
        }
    };
}
