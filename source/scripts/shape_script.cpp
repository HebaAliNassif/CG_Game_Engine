#include <iostream>
#include <entity.h>

using namespace CGEngine;

class shape_script : public Component
{
public:
    shape_script():Component("Script")
    {

    }
    void update(double deltaTime) override
    {
        if(!entity)exit(-1);
        Transform*t = entity->getComponent<Transform>();
        if(!t)exit(-1);
        glm::vec3 newPos=glm::vec3(t->getPosition().x,t->getPosition().y,t->getPosition().z+deltaTime*5);
        t->setPosition(newPos);

    }

};