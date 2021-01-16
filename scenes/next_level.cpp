#include <scene.h>
#include <camera.h>
#include <iostream>
namespace CGEngine
{
    class Next_Level : public CGEngine::Scene {
    public:

        Next_Level(Application_Manager *manager) : Scene(manager) {
            //Camera Entity
            Entity * camera = createEntity("Main Camera");
            camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);
        }
        void  start() override
        {
            std::cout<<"Good Job!\nPress space to go to next level";
        }
        void update(double deltaTime) override  {



        }
        ~Next_Level()
        {
        }
    };
}
