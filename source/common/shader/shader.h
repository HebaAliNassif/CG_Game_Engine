
#ifndef SHADER_H
#define SHADER_H

#include <application_manager.h>
#include <map>
#include <string>
namespace CGEngine {
    class Shader {

    public:

        // program id that shader objects are attached to
        GLuint programID;

        // Constructor
        Shader() {}

        // Asks GL to use this program for the upcoming operations.
        Shader &useShaderProgram();

        // Compiles the shader program from the given source codes
        void Compile(const char *vertexSource, const char *fragmentSource);


        GLuint getUniformLocation(const std::string &name);

        //A group of setter for uniform variables
        void set(const std::string &uniform, GLfloat value, bool useShader = false);

        void set(const std::string &uniform, GLint value, bool useShader = false);

        void set(const std::string &uniform, GLboolean value, bool useShader = false);

        void set(const std::string &uniform, glm::vec2 value, bool useShader = false);

        void set(const std::string &uniform, glm::vec3 value, bool useShader = false);

        void set(const std::string &uniform, glm::vec4 value, bool useShader = false);

        void set(const std::string &uniform, glm::mat4 value, GLboolean transpose = false, bool useShader = false);

        void destroy() {
            //Delete Shader Program
            if (programID != 0) glDeleteProgram(programID);
            programID = 0;
        }

    private:
        std::map<std::string, GLuint> uniform_location_cache;

        //Check and log for any error in the compilation process.
        void checkShaderCompilationErrors(GLuint shader);

        //Check and log for any error in the linking process.
        void checkProgramLinkingErrors(GLuint program);


    };
}

#endif //SHADER_H
