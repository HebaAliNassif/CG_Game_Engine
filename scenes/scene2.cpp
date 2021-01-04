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

        scene2()
        {
            CreateMaterials();

            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex30_light_array/light_array.frag","SimpleLightShader");
            Resource_Manager::LoadShader("assets/shaders/ex29_light/light_transform.vert","assets/shaders/ex32_textured_material/light_array.frag","TexturedLightShader");

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
            Plane->addComponent<Mesh_Component>()->setMeshModelName("plane");
            Plane->addComponent<Material_Component>()->setMaterialName("default_material");
            Plane->getComponent<Transform>()->setLocalPosition({0,0,0 });


            Entity* House = createEntity("House");
            House->addComponent<Transform>();
            House->addComponent<Mesh_Component>()->setMeshModelName("house");
            House->addComponent<Material_Component>()->setMaterialName("house_material");
            House->getComponent<Transform>()->setLocalPosition({0,0,10 });

            Entity* Sphere = createEntity("Sphere");
            Sphere->addComponent<Transform>();
            Sphere->addComponent<Mesh_Component>()->setMeshModelName("sphere");
            Sphere->addComponent<Material_Component>()->setMaterialName("default_material");
            Sphere->getComponent<Transform>()->setLocalPosition({0,5,0 });

            Entity* Cat = createEntity("Cat");
            Cat->addComponent<Transform>();
            Cat->addComponent<Mesh_Component>()->setMeshModelName("cat");
            Cat->addComponent<Material_Component>()->setMaterialName("cat_material");
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

        void onExit() override
        {
            getEntity("Main Camera")->getComponent<FlyController>()->release();
            Resource_Manager::clear();
            mesh_utils::clearMeshes();
        }

    };
}
