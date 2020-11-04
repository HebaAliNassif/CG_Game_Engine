#include <application.h>
#include <shader.h>
#include <irrKlang.h>
#include <iostream>

using namespace irrklang;


// This exercise Window Application that derives from "Application" parent
class EmptyWindowApplication : public CGEngine::Application {
    Shader program ;
    GLuint vertex_array = 0;

    glm::vec2 translation = glm::vec2(0,0);


    // This overriden function sets the window configuration params struct (title, size, isFullscreen).
    ISoundEngine* SoundEngine = createIrrKlangDevice();

    CGEngine::WindowConfiguration getWindowConfiguration() override {
        return { "Empty Window", {1280, 720}, false };
    }

    // onInitialize() function is called once before the application loop
    void onInitialize() override {
        //->play2D("audio/breakout.mp3", true);
        program = Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape1.frag","shape1");

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
            program = Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape1.frag","shape1");
        }
        else if(scancode==80||scancode==3)
        {
            program = Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape2.frag","shape2");
        }
        else if(scancode==81||scancode==4)
        {
            program = Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape3.frag","shape3");
        }
        else if(scancode==75||scancode==5)
        {
            program = Shader::LoadShader("assets/shaders/vshaders/screen.vert","assets/shaders/fshaders/shape4.frag","shape4");
        }
    }
    void onCursorMoveEvent(double x, double y) override{
        translation.x=x;
        translation.y=((y-720)*-1);
    }
};

// Example Entry point
int main(int argc, char** argv) {

    // Creates an instance of EmptyWindowApplication and call run on this instance
    return EmptyWindowApplication().run();
}
