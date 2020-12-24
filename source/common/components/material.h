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

    MaterialProperty<std::string> albedo_map("albedo_map","white");
    MaterialProperty<std::string> specular_map("specular_map","black");
    MaterialProperty<std::string> roughness_map("roughness_map","white");
    MaterialProperty<std::string> ambient_occlusion_map("ambient_occlusion_map","white");
    MaterialProperty<std::string> emissive_map("emissive_map","black");

    MaterialProperty<glm::vec3> albedo_tint("albedo_tint",{1.0f, 1.0f, 1.0f});
    MaterialProperty<glm::vec3> specular_tint("specular_tint",{1.0f, 1.0f, 1.0f});
    MaterialProperty<glm::vec3> emissive_tint("albedo_tint",{1.0f, 1.0f, 1.0f});

    MaterialProperty<glm::vec2> roughness_scale("roughness_scale",{0.0f, 1.0f});

    class Material : public Component {
    public:
        std::map<std::string, std::any> listOfMaterialProperties;

        Material();
        //TODO
        //Add the render state reference

        std::string shaderName;

        const std::string &getShaderName() const;

        void setShaderName(const std::string &shaderName);

        void bindUniforms() const;



    };
}

#endif //MATERIAL_H
