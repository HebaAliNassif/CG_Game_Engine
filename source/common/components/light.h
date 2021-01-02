#ifndef LIGHT_H
#define LIGHT_H

#include <shader/shader.h>
#include <application_manager.h>
#include "ecs/component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entity.h>
#include <iostream>
#include <iomanip>
#include <glm/vector_relational.hpp>
#include <transform.h>
#include <camera.h>
#include <fly-controller.h>


namespace CGEngine {

    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT
    };

    class Light : public Component {
    private:
        LightType type;
        bool enabled = true;
    public:
        bool isEnabled() const;

        void setEnabled(bool enabled);

    private:
        glm::vec3 diffuse =  {1,1,1}, specular =  {1,1,1}, ambient =  {0.1f, 0.1f, 0.1f};
        // This affects how the light will dim out as we go further from the light.
        // The formula is light_received = light_emitted / (a*d^2 + b*d + c) where a, b, c are the quadratic, linear and constant factors respectively.
        struct attenuation_struct{
            float constant = 0.0f, linear = 0.0f, quadratic = 1.0f;
        } attenuation; // Used for Point and Spot Lights only
        // This specifies the inner and outer cone of the spot light.
        // The light power is 0 outside the outer cone, the light power is full inside the inner cone.
        // The light power is interpolated in between the inner and outer cone.
        struct spot_angle_struct{
            float inner = glm::pi<float>()/4, outer = glm::pi<float>()/2;
        } spot_angle; // Used for Spot Lights only

    public:
        Light() : Component("light") {

        };

        Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool enabled);

        glm::vec3 getAmbient() const;

        glm::vec3 getDiffuse() const;

        glm::vec3 getSpecular() const;

        LightType getLightType() const;

        bool IsEnabled() const;

        spot_angle_struct getSpotAngle() const;


        void setAmbient(glm::vec3 ambient);

        void setDiffuse(glm::vec3 diffuse);

        void setSpecular(glm::vec3 specular);

        void setLightType(LightType type);

        void enable();

        void disable();

        void setAttenuation(float constant, float linear, float quadratic);

        void setSpotAngle(float inner, float outer);

        Transform *light_transform = nullptr;

        void onAdded() override;

        //void initialize();


        struct attenuation_struct getAttenuation() const;

    };



}
#endif //LIGHT_H