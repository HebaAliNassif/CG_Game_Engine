#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H
#include "ecs/component.h"
#include <glm/glm.hpp>
namespace CGEngine {

    struct HitInfo
    {
        bool isColliding;
        float distance;
        std::string name;
    public:
        HitInfo(bool _isCollding, float _distance,std::string _name) :
                isColliding(_isCollding), distance(_distance) ,name(_name){}
        bool IsColliding()
        {
            return 	isColliding;
        }
        float GetDistance()
        {
            return distance;
        }
        std::string GetName()
        {
            return name;
        }
    };

    class Box_Collider: public Component {
    public:
        Box_Collider(): Component("BoxCollider"){};
        Box_Collider(glm::vec3 _mMinExtent, glm::vec3 _mMaxExtent);

        glm::vec3 getMinExtent();
        glm::vec3 getMaxExtent();
        void setMinExtent(glm::vec3 point);
        void setMaxExtent(glm::vec3 point);

        void translateMinExtent(glm::vec3 amount);
        void translateMaxExtent(glm::vec3 amount);

        HitInfo onCollision( Box_Collider *other);
        std::string GetObjectName();
    private:
        glm::vec3 MinExtent;
        glm::vec3 MaxExtent;
    };

}
#endif //BOX_COLLIDER_H
