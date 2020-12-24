#include <scene.h>
#include <shader/shader.h>
#include <mesh.h>
#include <systems/fly-controller.h>
#include <application_manager.h>
#include <camera.h>
#include <render_system.h>
#include <mesh_component.h>
#include <shape_script.cpp>
#include <json/json.hpp>
#include <mesh-utils.hpp>
#include <resource_manager.h>
#include <texture/texture.h>
namespace CGEngine
{
    class scene2 : public CGEngine::Scene {
    public:
        Shader program;
        Shader program2;
        Mesh model;
        Mesh models;
        Mesh model2;
        GLuint texture;
        Texture mytexture;

        scene2()
        {
            program = Resource_Manager::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");
            program2 = Resource_Manager::LoadShader("assets/shaders/ex22_texture_sampling/transform.vert","assets/shaders/ex22_texture_sampling/texture.frag","shape3");
            mytexture = Resource_Manager::loadTexture("assets/models/House/House.jpeg",1,"Image");
            //Camera Entity
            Entity* camera = createEntity("Main Camera");
            camera->addComponent<Transform>()->setPosition(10,10,10);
            camera->getComponent<Transform>()->setForward({0, 0, 0});
            camera->addComponent<Camera>();
            camera->addComponent<FlyController>();



            //Shape Entity
            Entity* shape = createEntity("Shape");
            shape->addComponent<Transform>();
            shape->addComponent<Mesh_Component>();
            CGEngine::mesh_utils::Cuboid(model,true);
            shape->getComponent<Mesh_Component>()->setmesh(model);
            shape->getComponent<Mesh_Component>()->setProgram(program);
            shape->getComponent<Transform>()->setLocalPosition({0,0,0});
            shape->getComponent<Transform>()->setLocalScale({10,13,10});


            /*Entity* sphere = createEntity("sphere");
            sphere->addComponent<Transform>();
            sphere->addComponent<MeshC>();
            sphere->getComponent<MeshC>()->getmesh()-> Sphere( models,{32, 16}, true);
            sphere->getComponent<MeshC>()->setmesh(models);
            sphere->getComponent<MeshC>()->setProgram(program);
            sphere->getComponent<Transform>()->setLocalPosition({0,0,10});
            sphere->getComponent<Transform>()->setLocalScale({7,7,7});
            sphere->addComponent<shape_script>();*/


            mytexture.bind();
            Entity* House = createEntity("3DModel");
            House->addComponent<Transform>();
            House->addComponent<Mesh_Component>();
            CGEngine::mesh_utils::loadOBJ(model2, "assets/models/House/House.obj");
            House->getComponent<Mesh_Component>()->setmesh(model2);
            House->getComponent<Mesh_Component>()->setProgram(program2);
            House->getComponent<Transform>()->setLocalPosition({0,0,10});


            //Systems
            addSystem<RenderSystem>();
        }
        void  start() override
        {
        }
        void update(double deltaTime) override  {

        }
        ~scene2()
        {
            program.destroy();
            model.destroy();
            //camera_controller.release();
        }
    };
}
