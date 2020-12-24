#ifndef SYSTEM_H
#define SYSTEM_H
#include <application_manager.h>
#include <system.h>
#include <iostream>
#include <mesh_component.h>
#include <material.h>
namespace CGEngine
{
    class RenderSystem: public System
    {
    public:
        RenderSystem(){};
        void update(double delta_time) override
        {
            glClearColor(0, 0, 0, 0);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);

            glClearColor(0, 0, 0, 1);
            std::unordered_map<std::string,Entity*> ListOfEntities = this->scene->ListOfEntities;
            for (auto entity : ListOfEntities)
            {
                Transform *transform = entity.second->getComponent<Transform>();
                Mesh_Component *mesh = entity.second->getComponent<Mesh_Component>();
                Camera *camera = this->scene->getEntity("Main Camera")->getComponent<Camera>();
                Material * mat =  entity.second->getComponent<Material>();
                if(transform && mesh && camera && mat)
                {
                    glUseProgram(mat->getShader()->programID);
                    mat->getShader()->set("tint", glm::vec4(1, 1, 1, 1));
                    mat->getShader()->set("transform",camera->getVPMatrix()*transform->getLocalToWorldMatrix());
                    mesh->getmesh()->draw();
                }
            }
        }
    };
}
#endif //SYSTEM_H
