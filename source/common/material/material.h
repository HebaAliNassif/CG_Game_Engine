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
        BaseMaterialProperty() {};
        virtual void bindProperty(Shader*) = 0;
        template<class T>
        T *As() {
            return dynamic_cast<T *>(this);
        }
        template<class T>
        bool Is() const {
            const T *t = dynamic_cast<const T *>(this);
            return t != nullptr;
        }

    private:
    };

    template<typename T> class MaterialProperty : public BaseMaterialProperty {
        T value;
    public:
        MaterialProperty( T value) : value(value) {}
        void bindProperty(Shader* shader) override
        {
           // if(dynamic_cast<float>(value))shader->set("heba",dynamic_cast<float>(value));
        }
        T getValue() const {
            return value;
        }

        void setValue(T value) {
            MaterialProperty::value = value;
        }

        T *As() {
            return dynamic_cast<T *>(this);
        }
        template<class T>
        bool Is() const {
            const T *t = dynamic_cast<const T *>(this);
            return t != nullptr;
        }
    };

    class Material  {
    public:
        //Map for all created Material
        static std::map<std::string, Material*>listOfMaterials;
        //List of material properties
        std::map<std::string, BaseMaterialProperty*> listOfMaterialProperties;
        // creates a material
        static Material* createMaterial(std::string materialName);
        // retrieves a stored material
        static Material* getMaterial(std::string materialName);

        Material(){}
        //TODO
        //Add the render state reference
        std::string shaderName;
        const std::string &getShaderName() const;
        Shader* getShader() const;
        int GetShaderID() const;
        void setShaderName(const std::string &shaderName);
        void bindUniforms() const;

        template<class T>
        void addProperty(std::string propertyName, T value) {
            MaterialProperty<T>* property = new MaterialProperty<T>(value);
            listOfMaterialProperties[propertyName]=property;
        }

        template<class T>
        T *As() {
            return dynamic_cast<T *>(this);
        }
        template<class T>
        bool Is() const {
            const T *t = dynamic_cast<const T *>(this);
            return t != nullptr;
        }

    };

}

#endif //MATERIAL_H
