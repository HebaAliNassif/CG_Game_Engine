//
// Created by amalm on 11/28/2020.
//

#include "renderSystem.h"

void renderSystem::renderAll(vector<CGEngine::Entity*> entities) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < entities.size(); i++) {
        CGEngine::Transform *T = entities[i]->getComponent<CGEngine::Transform>();
        MeshC *M = entities[i]->getComponent<MeshC>();
        CGEngine::Camera *C = entities[i]->getComponent<CGEngine::Camera>();
        glUseProgram(entities[i]->getComponent<MeshC>()->getProgram()->programID);
        entities[i]->getComponent<MeshC>()->getProgram()->set("tint", glm::vec4(1, 1, 1, 1));
        if (T != nullptr && M != nullptr) {
            M->getProgram()->set("transform",C->getVPMatrix()*(T->getWorldToLocalMatrix()));
            M->getmesh()->draw();
        }
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}