#include <scene.h>
#include <mesh.h>
#include <systems/fly-controller.h>
#include <application_manager.h>
#include <camera.h>
#include <render_system.h>
#include <mesh_component.h>
#include <resource_manager.h>

namespace CGEngine
{
    class scene1 : public CGEngine::Scene {
    public:
        Shader* program;
        Mesh model;

        scene1(Application_Manager *manager) : Scene(manager) {
            program = Resource_Manager::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");

            //Camera Entity
            Entity* camera = createEntity("Main Camera");
            camera->addComponent<Transform>()->setPosition(10,10,10);
            camera->getComponent<Transform>()->setForward({0, 0, 0});
            camera->addComponent<Camera>();
            camera->addComponent<FlyController>();

/*
            //Shape Entity
            Entity* shape = createEntity("Shape");
            shape->addComponent<Transform>();
            shape->addComponent<Mesh_Component>();
            shape->getComponent<Mesh_Component>()->getmesh()-> Cuboid( model, true);
            shape->getComponent<Mesh_Component>()->setmesh(model);
            shape->getComponent<Mesh_Component>()->setProgram(*program);
            shape->getComponent<Transform>()->setLocalScale({7,2,7});*/


            //Systems
            addSystem<RenderSystem>();
        }
        void  start() override
        {

        }
        void update(double deltaTime) override  {



        }
        ~scene1()
        {
            program->destroy();
            model.destroy();
            //camera_controller.release();
        }
    };
}
