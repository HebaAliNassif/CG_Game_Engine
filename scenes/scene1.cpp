#include <scene.h>
#include <shader.h>
#include <mesh.h>
#include <systems/camera-controller.h>
#include <application_manager.h>
#include <camera.h>
#include <render_system.h>
#include <MeshC.h>
namespace CGEngine
{
    class scene1 : public CGEngine::Scene {
    public:
        Shader program;
        Mesh model;

        scene1()
        {
            program = Shader::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");

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
            shape->getComponent<MeshC>()->getmesh()-> Cuboid( model, true);
            shape->getComponent<MeshC>()->setmesh(model);
            shape->getComponent<MeshC>()->setProgram(program);
            shape->getComponent<Transform>()->setLocalScale({7,2,7});


            //Systems
            addSystem<CameraController>();
            addSystem<RenderSystem>();
        }
        void  start(Application_Manager* manager) override
        {

        }
        void update(double deltaTime) override  {



        }
        ~scene1()
        {
            program.destroy();
            model.destroy();
            //camera_controller.release();
        }
    };
}
