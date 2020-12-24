#include "scene.h"
#include <iostream>
//Adds entity to the scene.
CGEngine::Entity* CGEngine::Scene::createEntity(std::string name)
{
    m_LastEntityID++;
    EntityID id = m_LastEntityID;
    Entity* entity = new Entity(id,this);
    entity->scene=this;
    entity->name=name;
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


void CGEngine::Scene::onDestroy() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto  &e : ListOfEntities)
    {
        for(auto &c: e.second->ListOfComponents)
        {
            c->onExit();
        }
    }
    for (System* s : ListOfSystems)
    {
        if (s->enabled)
            s->onExit();
    }
}

void CGEngine::Scene::preUpdate(double deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto  &e : ListOfEntities)
    {
        for(auto &c: e.second->ListOfComponents)
        {
            c->update(deltaTime);
        }
    }

    for (System* s : ListOfSystems)
    {
        if (s->enabled)
            s->update(deltaTime);
    }
}

void CGEngine::Scene::onStart() {
    glClearColor(0, 0, 0, 0);
    for (auto  &e : ListOfEntities)
    {
        for(auto &c: e.second->ListOfComponents)
        {
            c->onAdded();
        }
    }

    std::sort(ListOfSystems.begin(), ListOfSystems.end(), [](System* a, System* b) {
        return a->priority < b->priority;
    });

    for (System* s : ListOfSystems)
    {
        s->start();
    }

}

bool CGEngine::Scene::Deserialize(const rapidjson::Value &obj) {
    return true;
}

bool CGEngine::Scene::Serialize(rapidjson::Writer<rapidjson::StringBuffer> *writer) const {
    writer->StartObject();
    for(auto &trans: rootTransforms)
    {
        trans->entity->Serialize(writer);
    }

    writer->EndObject();

    return true;
}