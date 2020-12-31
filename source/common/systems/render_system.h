#ifndef SYSTEM_H
#define SYSTEM_H
#include <application_manager.h>
#include <system.h>
#include <iostream>
#include <mesh_component.h>
#include <material/material.h>
#include <material_component.h>
#include <mesh-utils.hpp>
#include <light.h>

namespace CGEngine
{
    class RenderSystem: public System
    {
    public:
        RenderSystem(){};
        void update(double delta_time) override {
            glClearColor(0, 0, 0, 0);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);

            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);

            glClearColor(0, 0, 0, 1);
            std::unordered_map<std::string, Entity *> ListOfEntities = this->scene->ListOfEntities;
            std::vector<Light *> lights;

            //collect lights
            for (auto entity : ListOfEntities) {
                Light *light = entity.second->getComponent<Light>();
                if (light) {
                    lights.push_back(light);
                }
            }

            for (auto entity : ListOfEntities) {
                Transform *transform = entity.second->getComponent<Transform>();
                Mesh_Component *mesh = entity.second->getComponent<Mesh_Component>();
                Camera *camera = this->scene->getEntity("Main Camera")->getComponent<Camera>();
                Material_Component *mat_Component = entity.second->getComponent<Material_Component>();

                if (mat_Component) {

                    std::string matName = mat_Component->getMaterialName();
                    if (matName != "") {
                        Material *mat = Material::getMaterial(matName);

                        if (transform && mesh && camera && mat) {
                            glUseProgram(mat->getShader()->programID);
                            mat->getShader()->set("tint", glm::vec4(1, 1, 1, 1));
                            mat->getShader()->set("transform",
                                                  camera->getVPMatrix() * transform->getLocalToWorldMatrix());
                            mat->bindUniforms();

                            bindLightUniforms(lights, mat->getShader());

                            (CGEngine::mesh_utils::getMesh(mesh->getMeshModelName()))->draw();

                        }
                    }
                }
            }


        }
        void bindLightUniforms(std::vector<Light*>& lights, Shader* program) const {
            int light_index = 0;
            const int MAX_LIGHT_COUNT = 16;

            for(auto light : lights) {
                if(!light->isEnabled()) continue;
                std::string prefix = "lights[" + std::to_string(light_index) + "].";

                program->set(prefix + "diffuse", light->getDiffuse());
                program->set(prefix + "specular", light->getSpecular());
                program->set(prefix + "ambient", light->getAmbient());
                program->set(prefix + "type", static_cast<int>(light->getLightType()));


                switch (light->getLightType()) {
                    case LightType::DIRECTIONAL:
                        program->set(prefix + "direction", glm::normalize(light->light_transform->getForward()));
                        break;
                    case LightType::POINT:
                        program->set(prefix + "position", light->light_transform->getPosition());
                        program->set(prefix + "attenuation_constant", light->getAttenuation().constant);
                        program->set(prefix + "attenuation_linear", light->getAttenuation().linear);
                        program->set(prefix + "attenuation_quadratic", light->getAttenuation().quadratic);
                        break;
                    case LightType::SPOT:
                        program->set(prefix + "position", light->light_transform->getPosition());
                        program->set(prefix + "direction", glm::normalize(light->light_transform->getForward()));
                        program->set(prefix + "attenuation_constant", light->getAttenuation().constant);
                        program->set(prefix + "attenuation_linear", light->getAttenuation().linear);
                        program->set(prefix + "attenuation_quadratic", light->getAttenuation().quadratic);
                        program->set(prefix + "inner_angle", light->getSpotAngle().inner);
                        program->set(prefix + "outer_angle", light->getSpotAngle().outer);
                        break;
                }
                light_index++;
                if(light_index >= MAX_LIGHT_COUNT) break;
            }
            // Since the light array in the shader has a constant size, we need to tell the shader how many lights we sent.
            program->set("light_count", light_index);

        }

    };
}
#endif //SYSTEM_H
