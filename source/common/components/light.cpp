#include "light.h"
//
// Created by Maram on 28-Dec-20.
//

glm::vec3 CGEngine::Light::getAmbient() const
{
    return ambient;
}

glm::vec3 CGEngine::Light::getDiffuse() const
{
    return diffuse;
}

glm::vec3 CGEngine::Light::getSpecular() const
{
    return specular;
}

CGEngine::LightType CGEngine::Light::getLightType() const
{
    return type;
}

bool CGEngine::Light::IsEnabled() const
{
    return enabled;
}


struct CGEngine::Light::attenuation_struct CGEngine::Light::getAttenuation() const
{
    return attenuation;
}
struct CGEngine::Light::spot_angle_struct CGEngine::Light::getSpotAngle() const
{
    return spot_angle;
}


void CGEngine::Light::setLightType(LightType type_v) {
    type = type_v;
}


void CGEngine::Light::setAmbient(glm::vec3 ambient_v)
{
    ambient = ambient_v;
}

void CGEngine::Light::setDiffuse(glm::vec3 diffuse_v)
{
    diffuse = diffuse_v;
}

void CGEngine::Light::setSpecular(glm::vec3 specular_v)
{
    specular = specular_v;
}



void CGEngine::Light::enable()
{
    enabled = true;
}

void CGEngine::Light::disable()
{
    enabled = false;
}

void CGEngine::Light::setAttenuation(float constant_v, float linear_v, float quadratic_v) {
    attenuation.constant = constant_v;
    attenuation.linear = linear_v;
    attenuation.quadratic = quadratic_v;

}


void CGEngine::Light::setSpotAngle(float inner_v, float outer_v) {
    spot_angle.inner = inner_v;
    spot_angle.outer = outer_v;
}

void CGEngine::Light::onAdded() {

    if (!light_transform) {
    light_transform = this->getEntity()->getComponent<Transform>();
    //initialize();

    }
}

bool CGEngine::Light::isEnabled() const {
    return enabled;
}

void CGEngine::Light::setEnabled(bool enabled) {
    Light::enabled = enabled;
}

const glm::vec3 &CGEngine::Light::getColor() const {
    return color;
}

void CGEngine::Light::setColor(const glm::vec3 &color) {
    Light::color = color;
}
//float CGEngine::Light::getattenuationConstant() {
//    return attenuation.constant;
//}
/*
void CGEngine::Light::bindUniforms(std::vector<Light> lights) const {
    int light_index = 0;
    const int MAX_LIGHT_COUNT = 16;

    for(const auto& light : lights) {
        if(!light.enabled) continue;
        std::string prefix = "lights[" + std::to_string(light_index) + "].";

        program.set(prefix + "diffuse", light.diffuse);
        program.set(prefix + "specular", light.specular);
        program.set(prefix + "ambient", light.ambient);
        program.set(prefix + "type", static_cast<int>(light.type));


        switch (light.type) {
            case LightType::DIRECTIONAL:
                program.set(prefix + "direction", glm::normalize(light.light_transform->getForward()));
                break;
            case LightType::POINT:
                program.set(prefix + "position", light.light_transform->getPosition());
                program.set(prefix + "attenuation_constant", light.attenuation.constant);
                program.set(prefix + "attenuation_linear", light.attenuation.linear);
                program.set(prefix + "attenuation_quadratic", light.attenuation.quadratic);
                break;
            case LightType::SPOT:
                program.set(prefix + "position", light.light_transform->getPosition());
                program.set(prefix + "direction", glm::normalize(light.light_transform->getForward()));
                program.set(prefix + "attenuation_constant", light.attenuation.constant);
                program.set(prefix + "attenuation_linear", light.attenuation.linear);
                program.set(prefix + "attenuation_quadratic", light.attenuation.quadratic);
                program.set(prefix + "inner_angle", light.spot_angle.inner);
                program.set(prefix + "outer_angle", light.spot_angle.outer);
                break;
        }
        light_index++;
        if(light_index >= MAX_LIGHT_COUNT) break;
    }
    // Since the light array in the shader has a constant size, we need to tell the shader how many lights we sent.
    program.set("light_count", light_index);

}


*/



