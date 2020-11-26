#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
namespace CGEngine {

    class Entity;
    class Scene;

    enum componentType {
        transform,
        mesh
    };

    class Component {

        using EntityID = uint32_t;
    public:
        std::string name;
        bool enabled = true;
        Entity* entity = nullptr;
        Scene* scene = nullptr;
        EntityID entityId;

        EntityID getEntityId() const;

        void setEntityId(EntityID entityId);

        Entity *getEntity() const;

        void setEntity(Entity *entity);

        virtual std::string GetComponentName();

        Component(std::string Name) { name = Name; };

        virtual void onAdded(){};

        template<class T>
        bool Is() const {
            const T *t = dynamic_cast<const T *>(this);
            return t != nullptr;
        }

        template<class T>
        T *As() {
            return dynamic_cast<T *>(this);
        }

    };

/*#define COMPONENT(T)                            \
    protected:                                      \
        T() = default;                              \
    private:                                        \
        inline static std::vector<T*> components;     \
        static T* Create() { T* t = new T(); components.push_back(t); return t; };*/
}
#endif //COMPONENT_H
