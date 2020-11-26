#include "scene.h"
#include <iostream>
//Adds entity to the scene.
CGEngine::Entity* CGEngine::Scene::createEntity(std::string name)
{
    m_LastEntityID++;
    EntityID id = m_LastEntityID;
    Entity* entity = new Entity(id,this);
    entity->scene=this;
    ListOfEntities[name] = entity;
    return entity;
}

//Returns the specified entity from the scene.
CGEngine::Entity* CGEngine::Scene::getEntity(std::string name)
{
    auto entity = ListOfEntities.find(name);
    if (entity == ListOfEntities.end())
        return nullptr;
    return entity->second;
}

//Removes an entity from the scene.
void CGEngine::Scene::destroyEntity(std::string name)
{
    ListOfEntities.erase(name);
}

void CGEngine::Scene::addRootTransform(Transform* t)
{
    rootTransforms.push_back(t);

}
void CGEngine::Scene::removeRootTransform(Transform* t)
{
    auto pos = std::find(rootTransforms.begin(), rootTransforms.end(), t);
    if (pos == rootTransforms.end()) {
        return;
    }
    rootTransforms.erase(pos);
}

void CGEngine::Scene::start(Application_Manager* manager)
{
    std::sort(ListOfSystems.begin(), ListOfSystems.end(), [](System* a, System* b) {
        return a->priority < b->priority;
    });

    for (System* s : ListOfSystems)
    {
        s->start();
    }
}

void CGEngine::Scene::update(double deltaTime)
{

}


void CGEngine::Scene::onExit() {
    for (System* s : ListOfSystems)
    {
        if (s->enabled)
            s->onExit();
    }
}

void CGEngine::Scene::onDestroy() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CGEngine::Scene::preUpdate(double deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (System* s : ListOfSystems)
    {
        if (s->enabled)
            s->update(deltaTime);
    }
}

void CGEngine::Scene::onStart(Application_Manager* manager) {
    this->manager=manager;
    glClearColor(0, 0, 0, 0);
}
