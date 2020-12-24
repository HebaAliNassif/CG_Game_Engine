#pragma once
#ifndef SCENE_H
#define SCENE_H
#include "unordered_map"
#include "vector"
#include <ecs/entity.h>
#include <system.h>
#include <transform.h>
#include <application_manager.h>
#include <../serialization/json_base.h>

namespace CGEngine {
    using EntityID = uint32_t;
    class Scene :public JSONBase{
    private:
        Application_Manager* manager;
    protected:

        EntityID m_LastEntityID = 0;
    public:
        std::unordered_map<std::string,Entity*> ListOfEntities;

        std::vector<System*> ListOfSystems;
        std::vector<Transform*> rootTransforms;
        inline static Scene* current_scene = nullptr;

        virtual void start(){};
        virtual void update(double deltaTime){};
        virtual void onExit(){};

        void onStart();
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

        virtual bool Deserialize(const rapidjson::Value& obj) ;
        virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const ;


    };


}

#endif //SCENE_H
