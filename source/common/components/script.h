#ifndef SCRIPT_H
#define SCRIPT_H
#include <string>
#include <component.h>
namespace CGEngine
{
    class Script: public Component
    {
    public:
        std::string script_name;
        Script*script=nullptr;

        Script *getScript() const {
            return script;
        }

        void setScript(Script *script) {
            Script::script = script;
            script->entity=this->entity;
        }

        Script():Component("script"){};
        Script(std::string name):Component("script"),script_name(name){};

        virtual void start(){};
        virtual void update(double deltaTime){};
        virtual void onExit(){};

    };
}
#endif //SCRIPT_H
