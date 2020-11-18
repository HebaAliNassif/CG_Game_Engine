#ifndef SCENE_H
#define SCENE_H
#include "unordered_map"
#include "vector"
#include <ecs/entity.h>
#include <system.h>

namespace CGEngine {
    class Scene {
    protected:
        std::unordered_map<std::string,Entity*> ListOfEntities;
        std::vector<System*> ListOfSystems;
    public:

        void Start();
        void Update();

        //Adds entity to the scene.
        Entity* addEntity(std::string name);

        //Returns the specified entity to the scene.
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

        //Removes an entity from the scene.
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
