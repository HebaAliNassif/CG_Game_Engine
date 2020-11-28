#include <application_manager.h>
#include <shader.h>
#include <irrKlang.h>
#include <iostream>
#include <ecs/entity.h>
#include <transform.h>
#include <scene.h>
#include <camera.h>
#include "debug.h"
#include <scene1.cpp>
#include <scene2.cpp>

using namespace irrklang;

class manager : public CGEngine::Application_Manager {
    int scene=1;
    CGEngine::WindowConfiguration2 getWindowConfiguration() override {
        return {"Scene", {1280, 720}, false};
    }

    // onInitialize() function is called once before the application loop
    void onInitialize() override {
        CGEngine::Scene *scene2 = new CGEngine::scene2();
        goToScene(scene2);
        scene=2;
    }


    // onDraw(deltaTime) function is called every frame
    void onDraw(double deltaTime) override {

    }

    void onKeyEvent(int key, int scancode, int action, int mods) override {
        if ((scancode == 79 || scancode == 2) && scene!=2) {
            CGEngine::Scene *scene2 = new CGEngine::scene2();
            goToScene(scene2);
            scene=2;
        } else if ((scancode == 80 || scancode == 3) && scene!=1) {
            CGEngine::Scene *scene1 = new CGEngine::scene1();
            goToScene(scene1);
            scene=1;
        }

    }

    void onCursorMoveEvent(double x, double y) override {

    }
};

using namespace CGEngine;

void printTransformInfo(Transform *T) {
    std::cout << "Local To World Matrix: " << "\n";
    PrintMat4x4(T->getLocalToWorldMatrix());

    std::cout << "World To Local Matrix: " << "\n";
    PrintMat4x4(T->getWorldToLocalMatrix());

    std::cout << "Position: ";
    PrintVector3(T->getPosition());

    std::cout << "Local Position: ";
    PrintVector3(T->getLocalPosition());
}

int main(int argc, char **argv) {
    return manager().run();
}