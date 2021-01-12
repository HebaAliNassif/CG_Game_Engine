#include "box_collider.h"
#include <entity.h>
CGEngine::Box_Collider::Box_Collider(glm::vec3 pointMinExtent, glm::vec3 pointMaxExtent):Component("BoxCollider")
{
    this->MinExtent =   pointMinExtent;
    this->MaxExtent = pointMaxExtent;
}

glm::vec3 CGEngine::Box_Collider::getMinExtent()
{
    return MinExtent;
}
glm::vec3 CGEngine::Box_Collider::getMaxExtent()
{
    return MaxExtent;
}
void CGEngine::Box_Collider::setMinExtent(glm::vec3 point)
{
    this->MinExtent =   point;
}
void CGEngine::Box_Collider::setMaxExtent(glm::vec3 point)
{
    this->MaxExtent = point;
}

void CGEngine::Box_Collider::translateMinExtent(glm::vec3 amount)
{
    this->MinExtent += amount;
}
void CGEngine::Box_Collider::translateMaxExtent(glm::vec3 amount)
{
    this->MaxExtent += amount;
}

CGEngine::HitInfo CGEngine::Box_Collider::onCollision( Box_Collider *other)
{
    glm::vec3 distance1 = other->getMinExtent()-this->MaxExtent;
    glm::vec3 distance2 = this->MinExtent-other->getMaxExtent();
    glm::vec3 distance = glm::vec3(glm::max(distance1.x, distance2.x), glm::max(distance1.y, distance2.y), glm::max(distance1.z, distance2.z));
    float maxDistance = glm::max(distance.x, glm::max(distance.y, distance.z));
    return HitInfo(maxDistance < 0, maxDistance,other->entity->name);
}
