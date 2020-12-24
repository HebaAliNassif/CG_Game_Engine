#ifndef SCRIPT_SYSTEM_H
#define SCRIPT_SYSTEM_H
#include <system.h>

namespace CGEngine
{
    class ScriptSystem: public System
    {
    public:
       /* void start() override
        {
            this->priority=1;
            std::unordered_map<std::string,Entity*> ListOfEntities = this->scene->ListOfEntities;
            for (auto entity : ListOfEntities)
            {
                Script *script = entity.second->getComponent<Script>();
                if(script)
                {
                    script->script->start();
                }
            }
        }
        void update(double delta_time) override
        {
            std::unordered_map<std::string,Entity*> ListOfEntities = this->scene->ListOfEntities;
            for (auto entity : ListOfEntities)
            {
                Script *script = entity.second->getComponent<Script>();
                if(script)
                {
                    script->script->update(delta_time);
                }
            }
        }
        void onExit() override
        {
            std::unordered_map<std::string,Entity*> ListOfEntities = this->scene->ListOfEntities;
            for (auto entity : ListOfEntities)
            {
                Script *script = entity.second->getComponent<Script>();
                if(script)
                {
                    script->script->onExit();
                }
            }
        }*/
    };
}

#endif //SCRIPT_SYSTEM_H
