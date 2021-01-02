#include <scene.h>
#include <shader/shader.h>
#include <mesh.h>
#include <systems/fly-controller.h>
#include <application_manager.h>
#include <camera.h>
#include <light.h>
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
            //Resource_Manager::LoadShader("assets/shaders/vshaders/transform.vert","assets/shaders/fshaders/tint.frag","simpleShader");
            //Resource_Manager::LoadShader("assets/shaders/ex22_texture_sampling/transform.vert","assets/shaders/ex22_texture_sampling/texture.frag","3dShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex30_light_array/light_array.frag","SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex32_textured_material/light_array.frag","TexturedLightShader");
            //Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex29_light/spot_light.frag","SpotLightShader");

            CGEngine::mesh_utils::Cuboid("cube",true,glm::vec3(0,0,0),glm::vec3(5,5,5));
            CGEngine::mesh_utils::Sphere("sphere",glm::vec2(50,50),true,glm::vec3(0,0,0),1.0f);
            CGEngine::mesh_utils::Plane("plane", {1, 1}, false, {0, 0, 0}, {1, 1}, {0, 0}, {100, 100});

            CGEngine::mesh_utils::loadOBJ("house", "assets/models/House/House.obj");
            CGEngine::mesh_utils::loadOBJ("cat", "assets/models/Cat.obj");

            //Camera Entity
            Entity* camera = createEntity("Main Camera");
            camera->addComponent<Transform>()->setPosition(10,10,10);
            camera->getComponent<Transform>()->setForward({0, 0, 0});
            camera->addComponent<Camera>();
            camera->addComponent<FlyController>();


            Entity* Plane = createEntity("Plane");
            Plane->addComponent<Transform>()->setLocalScale(100,1,100);
            Plane->addComponent<Mesh_Component>();
            Plane->addComponent<Material_Component>()->setMaterialName("default_material");
            Plane->getComponent<Mesh_Component>()->setMeshModelName("plane");
            Plane->getComponent<Transform>()->setLocalPosition({0,0,0 });


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


            Entity* directional_light = createEntity("light_directional");
            directional_light->addComponent<Transform>();
            directional_light->addComponent<Light>()->setLightType(LightType::DIRECTIONAL);

            Entity* point_light = createEntity("light_point");
            point_light->addComponent<Transform>()->setPosition(0,1,0);
            point_light->addComponent<Light>()->setLightType(LightType::POINT);

            Entity* spot_light = createEntity("light_spot");
            spot_light->addComponent<Transform>()->setPosition(0,1,-10);
            spot_light->addComponent<Light>()->setLightType(LightType::SPOT);
            spot_light->getComponent<Light>()->setSpotAngle(1,1);


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
            getEntity("Main Camera")->getComponent<FlyController>()->release();
            program->destroy();
            model.destroy();

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
