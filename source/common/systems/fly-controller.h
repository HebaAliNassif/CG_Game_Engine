#ifndef Fly_CONTROLLER_HPP
#define Fly_CONTROLLER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include <camera.h>
#include <application_manager.h>
#include <iostream>
namespace CGEngine {

    // Allows you to control an object freely in world space
    class FlyController: public Component {
    private:
        Application_Manager* app;
        Transform* entity_transform = nullptr;

        float yaw, pitch;
        glm::vec3 position;

        float yaw_sensitivity, pitch_sensitivity;
        glm::vec3 position_sensitivity;
        float speedup_factor = 5.0f; // A speed multiplier if "Left Shift" is held.

        bool mouse_locked = false;

    public:
        FlyController():Component("FlyController"){};

        void onAdded() override
        {
            entity_transform = this->getEntity()->getComponent<Transform>();
            app = CGEngine::Application_Manager::getMainApp();

            if (!entity_transform)exit(-1);
            if (!app)exit(-1);

            initialize();
        }

        void initialize(){

            yaw_sensitivity = pitch_sensitivity = 0.01f;
            position_sensitivity = {3.0f, 3.0f, 3.0f};

            position = entity_transform->getPosition();
            yaw = glm::radians(entity_transform->getEulerAngles().y);
            pitch = glm::radians(entity_transform->getEulerAngles().x);

        }

        void release(){
            if(mouse_locked) {
                mouse_locked = false;
                app->getMouse().unlockMouse(app->getWindow());
            }
        }

        void update(double delta_time) override{
            if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouse_locked){
                app->getMouse().lockMouse(app->getWindow());
                mouse_locked = true;
            } else if(!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && mouse_locked) {
                app->getMouse().unlockMouse(app->getWindow());
                mouse_locked = false;
            }

            if(app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1)){
                glm::vec2 delta = app->getMouse().getMouseDelta();
                pitch -= delta.y * pitch_sensitivity;
                yaw -= delta.x * yaw_sensitivity;
            }

            if(pitch < -glm::half_pi<float>() * 0.99f) pitch = -glm::half_pi<float>() * 0.99f;
            if(pitch >  glm::half_pi<float>() * 0.99f) pitch  = glm::half_pi<float>() * 0.99f;
            yaw = glm::wrapAngle(yaw);

            glm::vec3 front = entity_transform->getForward(), up =  entity_transform->getUp(), right = entity_transform->getRight();

            glm::vec3 current_sensitivity = this->position_sensitivity;
            if(app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= speedup_factor;

            if(app->getKeyboard().isPressed(GLFW_KEY_W)) position += front * ((float)delta_time * current_sensitivity.z);
            if(app->getKeyboard().isPressed(GLFW_KEY_S)) position -= front * ((float)delta_time * current_sensitivity.z);
            if(app->getKeyboard().isPressed(GLFW_KEY_Q)) position += up * ((float)delta_time * current_sensitivity.y);
            if(app->getKeyboard().isPressed(GLFW_KEY_E)) position -= up * ((float)delta_time * current_sensitivity.y);
            if(app->getKeyboard().isPressed(GLFW_KEY_D)) position += right * ((float)delta_time * current_sensitivity.x);
            if(app->getKeyboard().isPressed(GLFW_KEY_A)) position -= right * ((float)delta_time * current_sensitivity.x);

            entity_transform->setPosition(position);
            entity_transform->setEulerAngles(glm::degrees(pitch),glm::degrees(yaw),0);
        }

        [[nodiscard]] float getYaw() const {return yaw;}
        [[nodiscard]] float getPitch() const {return pitch;}
        [[nodiscard]] glm::vec3 getPosition() const {return position;}

        [[nodiscard]] float getYawSensitivity() const {return yaw_sensitivity;}
        [[nodiscard]] float getPitchSensitivity() const {return pitch_sensitivity;}
        [[nodiscard]] glm::vec3 getPositionSensitivity() const {return position_sensitivity;}
        [[nodiscard]] float getSpeedUpFactor() const {return speedup_factor;}

        void setYaw(float _yaw){
            this->yaw = glm::wrapAngle(_yaw);
        }
        void setPitch(float _pitch){
            const float v = 0.99f*glm::pi<float>()/2;
            if(_pitch > v) _pitch = v;
            else if(_pitch < -v) _pitch = -v;
            this->pitch = _pitch;
        }
        void setPosition(glm::vec3 _pos){
            this->position = _pos;
        }

        void setYawSensitivity(float sensitivity){this->yaw_sensitivity = sensitivity;}
        void setPitchSensitivity(float sensitivity){this->pitch_sensitivity = sensitivity;}
        void setPositionSensitivity(glm::vec3 sensitivity){this->position_sensitivity = sensitivity;}
        bool Deserialize(const rapidjson::Value& obj) override
        {
            return true;
        }
        bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const override
        {
            return true;
        }
    };
}

#endif //Fly_CONTROLLER_H