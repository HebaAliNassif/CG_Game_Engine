#include <scene.h>
#include <camera.h>
#include <shader.h>
#include "iostream"
#include <mesh.h>
#include <camera-controller.h>
#include <mesh-utils.hpp>
#include <application_manager.h>
namespace CGEngine
{
    class scene2 : public CGEngine::Scene {
    public:
        Shader program;
        scene2()
        {
            Entity* shape = createEntity("shape");
            shape->addComponent<Transform>();
            shape->addComponent<Camera>();
        }
        void  start(Application_Manager* manager) override
        {
            //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        }
        void update(double deltaTime) override  {
        }
        ~scene2()
        {
        }
    };
}
