#include <scene.h>
#include <shader/shader.h>
#include <mesh.h>
#include <systems/fly-controller.h>
#include <application_manager.h>
#include <camera.h>
#include <render_system.h>
#include <mesh_component.h>
#include <shape_script.cpp>
#include <mesh-utils.hpp>
#include <resource_manager.h>
#include <material_component.h>
#include <material/material_assets.h>
namespace CGEngine
{


    class scene2 : public CGEngine::Scene {
    public:
        Shader* program;
        Shader* program2;
        Mesh model;
        Mesh models;
        Mesh model2;


        scene2()
        {
            CreateMaterials();
            Resource_Manager::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","simpleShader");
            Resource_Manager::LoadShader("assets/shaders/ex22_texture_sampling/transform.vert","assets/shaders/ex22_texture_sampling/texture.frag","3dShader");

            CGEngine::mesh_utils::Cuboid("cube",true,glm::vec3(0,0,0),glm::vec3(5,5,5));
            CGEngine::mesh_utils::Sphere("sphere",glm::vec2(50,50),true,glm::vec3(0,0,0),2.0f);

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("cat", "assets/models/Cat.obj");

            //Camera Entity
            Entity* camera = createEntity("Main Camera");
            camera->addComponent<Transform>()->setPosition(10,10,0);
            camera->getComponent<Transform>()->setForward({0, 0, 0});
            camera->addComponent<Camera>();
            camera->addComponent<FlyController>();


            Entity* Cube = createEntity("Cube");
            Cube->addComponent<Transform>();
            Cube->addComponent<Mesh_Component>();
            Cube->addComponent<Material_Component>()->setMaterialName("default_material");
            Cube->getComponent<Mesh_Component>()->setMeshModelName("cube");
            Cube->getComponent<Transform>()->setLocalPosition({0,0,0 });


            Entity* House = createEntity("House");
            House->addComponent<Transform>();
            House->addComponent<Mesh_Component>();
            House->addComponent<Material_Component>()->setMaterialName("house_material");
            House->getComponent<Mesh_Component>()->setMeshModelName("house");
            House->getComponent<Transform>()->setLocalPosition({0,0,10 });

            Entity* Sphere = createEntity("Sphere");
            Sphere->addComponent<Transform>();
            Sphere->addComponent<Mesh_Component>();
            Sphere->addComponent<Material_Component>()->setMaterialName("default_material");
            Sphere->getComponent<Mesh_Component>()->setMeshModelName("sphere");
            Sphere->getComponent<Transform>()->setLocalPosition({0,5,0 });

            Entity* Cat = createEntity("Cat");
            Cat->addComponent<Transform>();
            Cat->addComponent<Mesh_Component>();
            Cat->addComponent<Material_Component>()->setMaterialName("cat_material");
            Cat->getComponent<Mesh_Component>()->setMeshModelName("cat");
            Cat->getComponent<Transform>()->setLocalPosition({0,0,-10 });
            Cat->getComponent<Transform>()->setLocalScale(5.0f);
            Cat->getComponent<Transform>()->setLocalEulerAngles(0,90,0);




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
            program->destroy();
            model.destroy();
            //camera_controller.release();
        }
        void checkerBoard(GLuint texture, glm::ivec2 size, glm::ivec2 patternSize, Color color1, Color color2){
            auto* data = new Color[size.x * size.y];
            int ptr = 0;
            for(int y = 0; y < size.y; y++){
                for(int x = 0; x < size.x; x++){
                    data[ptr++] = ((x/patternSize.x)&1)^((y/patternSize.y)&1)?color1:color2;
                }
            }
            glBindTexture(GL_TEXTURE_2D, texture);
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            delete[] data;
        }

    };
}
