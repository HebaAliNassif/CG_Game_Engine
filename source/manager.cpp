#include <application_manager.h>
#include <shader/shader.h>
#include <irrKlang.h>
#include <iostream>
#include <scene.h>
#include <camera.h>
#include <scene1.cpp>
#include <scene2.cpp>
#include <../debug.h>
using namespace irrklang;

class manager : public CGEngine::Application_Manager {
    int scene=1;
    CGEngine::WindowConfiguration2 getWindowConfiguration() override {
        return {"Scene", {1280, 720}, false};
    }

    // onInitialize() function is called once before the application loop
    void onInitialize() override {
        CGEngine::Scene *scene2 = new CGEngine::scene2(this);
        goToScene(scene2);
        scene=2;
    }


    // onDraw(deltaTime) function is called every frame
    void onDraw(double deltaTime) override {

    }

    void onKeyEvent(int key, int scancode, int action, int mods) override {
    }

    void onCursorMoveEvent(double x, double y) override {

    }
    void onDestroy() override
    {
        delete current_scene;
    }
};

using namespace CGEngine;

int main(int argc, char **argv) {
    return manager().run();
}