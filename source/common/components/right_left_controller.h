#ifndef RIGHT_LEFT_CONTROLLER_H
#define RIGHT_LEFT_CONTROLLER_H
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <box_collider.h>
#include <camera.h>
#include <application_manager.h>
#include <iostream>
namespace CGEngine {

    // Allows you to control an object freely in world space
    class RightLeftController: public Component {
    private:
        Application_Manager* app;
        Transform* entity_transform = nullptr;
        Box_Collider* boxCollider;

        glm::vec3 position;
        glm::vec3 position_sensitivity;
        float speedup_factor = 5.0f; // A speed multiplier if "Left Shift" is held.
        bool  rotate = false;
        bool mouse_locked = false;

    public:
        RightLeftController():Component("RightLeftController"){};
        bool freeze_movement_right = false;
        bool freeze_movement_left = false;
        bool freeze_movement_down = false;
        bool freeze_movement_up = false;
        void onAdded() override
        {
            entity_transform = this->getEntity()->getComponent<Transform>();
            app = CGEngine::Application_Manager::getMainApp();

            if (!entity_transform)exit(-1);
            if (!app)exit(-1);

            initialize();
        }

        void initialize(){

            position_sensitivity = {5.0f, 5.0f, 5.0f};
            position = entity_transform->getPosition();

        }

        void release(){
            if(mouse_locked) {
                mouse_locked = false;
                app->getMouse().unlockMouse(app->getWindow());
            }
        }

        void update(double delta_time) override{



            glm::vec3 front = entity_transform->getForward(), up =  entity_transform->getUp(), right = entity_transform->getRight();

            glm::vec3 current_sensitivity = this->position_sensitivity;
            if(app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= speedup_factor;

            if(! freeze_movement_up&&(app->getKeyboard().isPressed(GLFW_KEY_UP )|| app->getKeyboard().isPressed( GLFW_KEY_W)))
            {
                entity_transform->setEulerAngles(0,180,0);
                front = entity_transform->getForward();
                position -= front * (((float)delta_time * current_sensitivity.z));
                if(freeze_movement_down)freeze_movement_down = false;
            }
            if(!freeze_movement_down&&(app->getKeyboard().isPressed( GLFW_KEY_DOWN)||app->getKeyboard().isPressed( GLFW_KEY_S)))
            {
                entity_transform->setEulerAngles(0,0,0);
                front = entity_transform->getForward();
                position -= front * ((float)delta_time * current_sensitivity.z);
                if(freeze_movement_up)freeze_movement_up=false;
            }

            if(! freeze_movement_right&& (app->getKeyboard().isPressed(GLFW_KEY_RIGHT)|| app->getKeyboard().isPressed( GLFW_KEY_D)))
            {
                entity_transform->setEulerAngles(0,90,0);
                glm::vec3 front = entity_transform->getForward();
                position -= front * ((float)delta_time * current_sensitivity.x);
                if(freeze_movement_left)freeze_movement_left=false;
            }
            if(!freeze_movement_left&& (app->getKeyboard().isPressed(GLFW_KEY_LEFT)|| app->getKeyboard().isPressed( GLFW_KEY_A)))
            {

                entity_transform->setEulerAngles(0,-90,0);
                glm::vec3 front = entity_transform->getForward();
                position -= front * ((float)delta_time * current_sensitivity.x);
                if(freeze_movement_right)freeze_movement_right=false;

            }

            entity_transform->setPosition(position);
        }


        [[nodiscard]] glm::vec3 getPosition() const {return position;}


        [[nodiscard]] glm::vec3 getPositionSensitivity() const {return position_sensitivity;}
        [[nodiscard]] float getSpeedUpFactor() const {return speedup_factor;}


        void setPosition(glm::vec3 _pos){
            this->position = _pos;
        }

        void setPositionSensitivity(glm::vec3 sensitivity){this->position_sensitivity = sensitivity;}
        void resetcontrollers()
        {
            freeze_movement_right = false;
            freeze_movement_left = false;
            freeze_movement_down = false;
            freeze_movement_up = false;
        }
    };
}
#endif //RIGHT_LEFT_CONTROLLER_H
