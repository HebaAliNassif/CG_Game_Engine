#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/glm.hpp>
#include <application_manager.h>
#include "ecs/component.h"
#include <resource_manager.h>
#include <map>
#include <any>
namespace CGEngine {

    class BaseMaterialProperty
    {
    public:
        BaseMaterialProperty(const std::string &name) : name(name){};

    private:
        std::string name;
    };
    template<typename T> class MaterialProperty : public BaseMaterialProperty {
        T value;
    public:
        MaterialProperty(std::string name, T value) : value(value), BaseMaterialProperty(name)  {}

        T getValue() const {
            return value;
        }

        void setValue(T value) {
            MaterialProperty::value = value;
        }
    };



    class Material : public Component {
    public:
        std::map<std::string, std::any> listOfMaterialProperties;


        Material():Component("Material")
        {
        }
        //TODO
        //Add the render state reference

        std::string shaderName;

        const std::string &getShaderName() const;

        Shader* getShader() const;

        int GetShaderID() const;

        void setShaderName(const std::string &shaderName);

        void bindUniforms() const;


    };
}

#endif //MATERIAL_H
