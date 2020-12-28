#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H
#include <component.h>
#include <material/material.h>
namespace CGEngine {
    class Material_Component : public Component {
   std::string materialName = "";
    public:
        Material_Component():Component("Material_Component"){};

        const std::string &getMaterialName() const {
            return materialName;
        }

        void setMaterialName(const std::string &materialName) {
            Material_Component::materialName = materialName;
        }





    };
}


#endif //MATERIAL_COMPONENT_H
