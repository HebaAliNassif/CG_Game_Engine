#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/glm.hpp>
#include <application_manager.h>
#include "ecs/component.h"
#include <resource_manager.h>
#include <map>
#include <any>
#include <RenderState.h>
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
          // shader->set("heba",(T)(value));
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
        RenderState *renderState;
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

        std::string shaderName;
        const std::string &getShaderName() const;
        Shader* getShader() const;
        int GetShaderID() const;
        void setShaderName(const std::string &shaderName);
        void bindUniforms() const;
        void setRenderState(RenderState* state);
        RenderState *getRenderState();
        template<class T>
        void addProperty(std::string propertyName, T value) {
            MaterialProperty<T>* property = new MaterialProperty<T>(value);
            listOfMaterialProperties[propertyName]=property;
        }

        template<class T>
        T getPropertyValue(std::string propertyName) {
           // MaterialProperty<T>* property = new MaterialProperty<T>(value);
            return (listOfMaterialProperties[propertyName]->As<MaterialProperty<T>>())->getValue();
        }

        template<class T>
        void updatePropertyValue(std::string propertyName, T value) {
            // MaterialProperty<T>* property = new MaterialProperty<T>(value);
             (listOfMaterialProperties[propertyName]->As<MaterialProperty<T>>())->setValue(value);
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
