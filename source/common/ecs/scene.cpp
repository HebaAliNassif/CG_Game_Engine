#include "scene.h"
//Adds entity to the scene.
CGEngine::Entity* CGEngine::Scene::addEntity(std::string name)
{
    Entity* entity = new Entity();
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

