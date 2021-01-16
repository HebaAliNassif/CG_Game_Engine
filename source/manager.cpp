#include <application_manager.h>
#include <shader/shader.h>
#include <iostream>
#include <scene.h>
#include <menu.cpp>
#include <gameover.cpp>
#include <game_scene.cpp>
#include <irrKlang.h>
using namespace irrklang;
class manager : public CGEngine::Application_Manager {
    int level = 1;

    CGEngine::WindowConfiguration2 getWindowConfiguration() override {
        return {"Scene", {1280, 720}, false};
    }

    // onInitialize() function is called once before the application loop
    void onInitialize() override {
        CGEngine::Scene *Scene = new CGEngine::Menu(this);
        goToScene(Scene);
    }

    // onDraw(deltaTime) function is called every frame
    void onDraw(double deltaTime) override {

    }

    void onKeyEvent(int key, int scancode, int action, int mods) override {
        if(getKeyboard().isPressed(GLFW_KEY_SPACE) && dynamic_cast<CGEngine::Menu*>(current_scene))
        {
            level = 1;
            CGEngine::Scene *Scene = new CGEngine::Game_Scene(this, level);
            goToScene(Scene);
        }
        if(getKeyboard().isPressed(GLFW_KEY_SPACE) && dynamic_cast<CGEngine::Next_Level*>(current_scene))
        {
            level++;
            CGEngine::Scene *Scene = new CGEngine::Game_Scene(this, level);
            goToScene(Scene);
        }
        if(getKeyboard().isPressed(GLFW_KEY_SPACE) && dynamic_cast<CGEngine::Gameover*>(current_scene))
        {
            level = 1;
            CGEngine::Scene *Scene = new CGEngine::Game_Scene(this, level);
            goToScene(Scene);
        }
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