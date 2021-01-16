#include <scene.h>
#include <camera.h>
#include <iostream>
namespace CGEngine
{
    class Menu : public CGEngine::Scene {
    public:


        Menu(Application_Manager *manager) : Scene(manager) {

            //Camera Entity
            Entity * camera = createEntity("Main Camera");
            camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);

        }
        void  start() override
        {
            std::cout<<"Press space to start the game\n";
        }
        void update(double deltaTime) override  {



        }
        ~Menu()
        {
        }
    };
}
