/*#include <application.h>
#include <shader.h>
#include <irrKlang.h>
#include <iostream>
#include <ecs/entity.h>
#include <transform.h>
#include <scene.h>
#include <camera.h>
#include "debug.h"
using namespace irrklang;



class MainScrean : public CGEngine::Application {
    Shader program ;
    GLuint vertex_array = 0;

    glm::vec2 translation = glm::vec2(0,0);
    ISoundEngine *SoundEngine=createIrrKlangDevice();
    // This overriden function sets the window configuration params struct (title, size, isFullscreen).
    CGEngine::WindowConfiguration getWindowConfiguration() override {
        return { "Empty Window", {1280, 720}, false };
    }

    // onInitialize() function is called once before the application loop
    void onInitialize() override {
        SoundEngine->play2D("audio/breakout.mp3", true);
        program = Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape1.frag","shape1");
        Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape2.frag","shape2");
        Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape3.frag","shape3");
        Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape4.frag","shape4");

        translation=Application::getMouse().getMousePosition();
        glGenVertexArrays(1, &vertex_array);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    void onImmediateGui(ImGuiIO &io) override {
        // Shows a metric window just as an example of ImGui operations
        // ImGui::ShowMetricsWindow();
    }

    // onDraw(deltaTime) function is called every frame
    void onDraw(double deltaTime) override {
        //At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame.
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program.programID);

        GLuint translation_uniform_location = glGetUniformLocation(program.programID, "translation");
        glUniform2f(translation_uniform_location, translation.x, translation.y);


        glBindVertexArray(vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    void onKeyEvent(int key, int scancode, int action, int mods) override{

        if(scancode==79||scancode==2)
        {
            program = Shader::Shaders["shape1"];
        }
        else if(scancode==80||scancode==3)
        {
            program = Shader::Shaders["shape2"];
        }
        else if(scancode==81||scancode==4)
        {
            program = Shader::Shaders["shape3"];
        }
        else if(scancode==75||scancode==5)
        {
            program = Shader::Shaders["shape4"];
        }
    }
    void onCursorMoveEvent(double x, double y) override{
        translation.x=x;
        translation.y=((y-720)*-1);
    }
};
using namespace CGEngine ;

void printTransformInfo(Transform* T) {
    std::cout << "Local To World Matrix: " << "\n";
    PrintMat4x4(T->getLocalToWorldMatrix());

    std::cout << "World To Local Matrix: " << "\n";
    PrintMat4x4(T->getWorldToLocalMatrix());

    std::cout << "Position: ";
    PrintVector3(T->getPosition());

    std::cout << "Local Position: ";
    PrintVector3(T->getLocalPosition());
}
    /*std::cout<<"Rotation: ";
    std::cout<<T->getLocalEulerAngles().x<<"  "<<T->getLocalEulerAngles().y<<"  "<<T->getLocalEulerAngles().z<<"\n";

    std::cout<<"Scale: ";
    PrintVector3(T->getLocalScale());
}

// Example Entry point
int main(int argc, char** argv) {
    Scene World;

    Entity* shape = World.createEntity("shape");;
    shape->addComponent<Transform>();
    shape->addComponent<Camera>();
    Transform *T =shape->getComponent<Transform>();

    Entity* Parent = World.createEntity("parent");;
    Parent->addComponent<Transform>();
    Transform *TParent =Parent->getComponent<Transform>();
    TParent->setPosition(2,2,2);
    TParent->setLocalScale(5,5,5);
    //T->setPosition(3,3,3);


    std::cout<<"Shape Info: \n";
    printTransformInfo(T);
    std::cout<<"ParentShape Info: \n";
    printTransformInfo(TParent);

    T->setParent(TParent,true);

    std::cout<<"Shape Info: (After Parenting)\n";
    printTransformInfo(T);
    std::cout<<"ParentShape Info: (After Parenting)\n";
    printTransformInfo(TParent);
    return 0;
    // Creates an instance of EmptyWindowApplication and call run on this instance
    return MainScrean().run();
}
*/
