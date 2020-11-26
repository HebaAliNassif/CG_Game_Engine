#include "component.h"
#include <entity.h>
CGEngine::Entity *CGEngine::Component::getEntity() const {
    return entity;
}

void CGEngine::Component::setEntity(Entity *entity) {
    Component::entity = entity;
}

std::string CGEngine::Component::GetComponentName()
{
    return name;
}

CGEngine::Component::EntityID CGEngine::Component::getEntityId() const {
    return entityId;
}

void CGEngine::Component::setEntityId(unsigned int entityId) {
    Component::entityId = entityId;
}
