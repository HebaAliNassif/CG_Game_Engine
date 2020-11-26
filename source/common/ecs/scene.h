#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "unordered_map"
#include "vector"
#include <ecs/entity.h>
#include <system.h>
#include <transform.h>
#include <application_manager.h>
namespace CGEngine {
    using EntityID = uint32_t;
    class Scene {
    private:
        Application_Manager* manager;
    protected:
        std::unordered_map<std::string,Entity*> ListOfEntities;
        //std::unordered_map<std::string,System*> ListOfSystems;

        std::vector<System*> ListOfSystems;
        std::vector<Transform*> rootTransforms;
        EntityID m_LastEntityID = 0;
    public:
        inline static Scene* current_scene = nullptr;

        virtual void start(Application_Manager* manager);
        virtual void update(double deltaTime);
        virtual void onExit();

        void onStart(Application_Manager* manager);
        void preUpdate(double deltaTime);
        void onDestroy();
        const auto& GetRootTransforms() { return rootTransforms; }
        void addRootTransform(Transform* t);
        void removeRootTransform(Transform* t);


        //Create an entity and add it to the scene.
        Entity* createEntity(std::string name);

        //Return the specified entity from the scene.
        Entity* getEntity(std::string name);

        //Removes an entity from the scene.
        void destroyEntity(std::string name);

        //Adds system to the scene.
        template<class T>
        T* addSystem()
        {
            for (auto system : ListOfSystems)
            {
                T* t = system->As<T>();
                if (t != nullptr)
                    return nullptr;
            }
            T* system = new T();
            ListOfSystems.push_back(system);
            system->scene = this;
            system->onAdded();

            return system;
        }

        //Returns the specified system from the scene.
        template<class T>
        T* getSystem()
        {
            for (auto system : ListOfSystems)
            {
                T* t = system->As<T>();
                if (t != nullptr)
                    return t;
            }
            return nullptr;
        }

        //Removes the specified system from the scene.
        template<class T>
        void destroySystem()
        {
            for (auto system : ListOfSystems)
            {
                T* t = system->As<T>();
                if (t != nullptr) {
                    ListOfSystems.erase(std::remove(ListOfSystems.begin(), ListOfSystems.end(), t), ListOfSystems.end());
                }
            }
        }

    };
}

#endif //SCENE_H
