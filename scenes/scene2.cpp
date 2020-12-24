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
#include <material.h>
#include <resource_manager.h>
#include <texture/texture.h>


namespace CGEngine
{


    class scene2 : public CGEngine::Scene {
    public:
        Shader* program;
        Shader* program2;
        Mesh model;
        Mesh models;
        Mesh model2;
        Texture HouseTexture;
        Texture FloorTexture;
        scene2()
        {
            program = Resource_Manager::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","shape1");
            program2 = Resource_Manager::LoadShader("assets/shaders/ex22_texture_sampling/transform.vert","assets/shaders/ex22_texture_sampling/texture.frag","shape3");
            HouseTexture = Resource_Manager::loadTexture("assets/models/House/House.jpeg",1,"Image");
            FloorTexture = Resource_Manager::loadTexture("assets/models/CatAlbedo.jpg",1,"Image22");


            //Camera Entity
            Entity* camera = createEntity("Main Camera");
            camera->addComponent<Transform>()->setPosition(10,10,10);
            camera->getComponent<Transform>()->setForward({0, 0, 0});
            camera->addComponent<Camera>();
            camera->addComponent<FlyController>();


            HouseTexture.bind();
            Entity* House = createEntity("House");
            House->addComponent<Transform>();
            House->addComponent<Mesh_Component>();
            House->addComponent<Material>()->setShaderName("shape3");
            CGEngine::mesh_utils::loadOBJ(model2, "assets/models/House/House.obj");
            House->getComponent<Mesh_Component>()->setmesh(model2);
            House->getComponent<Transform>()->setLocalPosition({0,0,0   });

           /* //checkerBoard(FloorTexture.textureID, {256,256}, {128,128}, {255, 255, 255, 255}, {16, 16, 16, 255});

            //Shape Entity
            Entity* shape = createEntity("Floor");
            shape->addComponent<Transform>();
            shape->addComponent<Mesh_Component>();
            CGEngine::mesh_utils::Plane(model,{1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});
            FloorTexture.bind();
            shape->getComponent<Mesh_Component>()->setmesh(model);
            shape->getComponent<Mesh_Component>()->setProgram(program2);
            shape->getComponent<Transform>()->setLocalPosition({0,0,0});
            shape->getComponent<Transform>()->setLocalScale({10,13,10});



            //HouseTexture.bind();

*/

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
