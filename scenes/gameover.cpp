#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <scene.h>
#include <camera.h>
#include <iostream>
#include <irrKlang.h>
using namespace irrklang;
namespace CGEngine
{
    class Gameover : public CGEngine::Scene {
    public:

        ISoundEngine *SoundEngine = createIrrKlangDevice();

        Gameover(Application_Manager *manager) : Scene(manager) {

            //Camera Entity
            Entity * camera = createEntity("Main Camera");
            camera->addComponent<Transform>();
            camera->addComponent<Camera>()->setType(CameraType::Perspective);

        }
        void  start() override
        {
            SoundEngine->play2D("audio/scream.mp3", false);
            std::cout<<"Game Over\nPress space to play again or m to back to main menu\n";
        }
        void update(double deltaTime) override  {

        }
        ~Gameover()
        {
        }
    };
}
#endif //GAMEOVER_H
