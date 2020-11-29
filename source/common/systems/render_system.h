#ifndef SYSTEM_H
#define SYSTEM_H
#include <application_manager.h>
#include <system.h>
#include <iostream>
#include <MeshC.h>
namespace CGEngine
{
    class RenderSystem: public System
    {
    public:
        RenderSystem(){};
        void update(double delta_time) override
        {
            std::unordered_map<std::string,Entity*> ListOfEntities = this->scene->ListOfEntities;
            for (auto entity : ListOfEntities)
            {
                Transform *transform = entity.second->getComponent<Transform>();
                MeshC *mesh = entity.second->getComponent<MeshC>();
                Camera *camera = this->scene->getEntity("Main Camera")->getComponent<Camera>();

                if(transform && mesh && camera)
                {
                    glUseProgram(entity.second->getComponent<MeshC>()->getProgram()->programID);

                    entity.second->getComponent<MeshC>()->getProgram()->set("tint", glm::vec4(1, 1, 1, 1));

                    mesh->getProgram()->set("transform",camera->getVPMatrix()*glm::transpose(transform->getLocalToWorldMatrix()));
                    mesh->getmesh()->draw();
                }
            }
        }
    };
}
#endif //SYSTEM_H
