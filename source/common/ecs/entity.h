#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <unordered_map>
#include <vector>
#include "component.h"
#include <transform.h>
#include <algorithm>
namespace CGEngine {

    struct Node{
        int value=-1;
    };
    class Entity {
        using EntityID = uint32_t;
        friend class Scene;
    public:
        //List of components that is owned by the entity.
        std::vector<Component*> ListOfComponents;
        Scene* scene = nullptr;
        EntityID ID;
        Entity::Entity(EntityID entityID, Scene* scene) : ID(entityID),scene(scene)
        {
        }

        Scene *getScene() const {
            return scene;
        }

        void setScene(Scene *scene) {
            Entity::scene = scene;
        }

        //Adds component to the entity and returns true if added.
        template<class T>
        T* addComponent()
        {
            for (auto comp : ListOfComponents)
            {
                T* t = comp->As<T>();
                if (t != nullptr)
                    return nullptr;
            }
            T* comp = new T();
            comp->setEntityId(this->ID);
            comp->entity=this;
            comp->onAdded();
            ListOfComponents.push_back(comp);
            return comp;
        }

        //Returns the component of componentType type if the entity has one attached, null if it doesn't.
        template<class T>
        T* getComponent() {
            for (auto comp : ListOfComponents)
            {
                T* t = comp->As<T>();
                if (t != nullptr)
                    return t;
            }
            return nullptr;
        }

        //Removes a component in the entity.
        template<class T>
        void destroyComponent()
        {
            for (auto comp : ListOfComponents)
            {
                T* t = comp->As<T>();
                if (t != nullptr) {
                    ListOfComponents.erase(std::remove(ListOfComponents.begin(), ListOfComponents.end(), t), ListOfComponents.end());
                }
            }
        }

        template<class T>
        bool Is() const {
            const T *t = dynamic_cast<const T *>(this);
            return t != nullptr;
        }

        template<class T>
        T *As() {
            return dynamic_cast<T *>(this);
        }

    /*
       //Removes the entity.
        void destroyEntity();
        //Returns all components of componentType type in the entity.
        template<class T>
        std::vector<T*> getComponents()
        {
            vector<T*> Components;
            for (auto comp : ListOfComponents)
            {
                T* t = comp->As<T>();
                if (t != nullptr) {
                    Components.push_back(t);
                }
            }
            return Components;
        }
        //Removes all the component of componentType type in the entity.
        //t is an optional amount of time to delay before destroying the component.
        template<class T>
        void destroyComponents(float t = 0.0F)
        {

        }
         //Destructor
        // ~Entity();
        */
    };
}
#endif //ENTITY_H
