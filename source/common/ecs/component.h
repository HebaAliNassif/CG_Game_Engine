#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
namespace CGEngine {

    enum componentType {
        transform,
        mesh
    };

    class Component {


    public:
        std::string name;
        bool enabled = true;

        virtual std::string GetComponentName() { return name; }

        Component(std::string Name) { name = Name; };

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
