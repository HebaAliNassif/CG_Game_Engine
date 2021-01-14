//
// Created by Maram on 14-Jan-21.
//

#ifndef COMPUTER_GRAPHICS_PROJECT_ENEMY_MOVEMENT_H
#define COMPUTER_GRAPHICS_PROJECT_ENEMY_MOVEMENT_H

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <box_collider.h>
#include <camera.h>
#include <application_manager.h>
#include <iostream>

namespace CGEngine {
    class EnemyMovement: public Component {
    private:
        Application_Manager* app;
        Transform* entity_transform = nullptr;
        Box_Collider* boxCollider;

        glm::vec3 position;
        glm::vec3 position_sensitivity;
        float speedup_factor = 5.0f; // A speed multiplier if "Left Shift" is held.

        bool mouse_locked = false;
        bool isHorizontal;
        float finishPathPercent;
        bool increment;

        vec3  start;
        vec3 end;


    public:
        void setStart(const vec3 &start) {
            EnemyMovement::start = start;
        }


        void setEnd(const vec3 &End) {
            end = End;
        }


        float getFinishPathPercent() const {
            return finishPathPercent;
        }

        void setFinishPathPercent(float finishPathPercent) {
            EnemyMovement::finishPathPercent = finishPathPercent;
        }



        bool getIncrement() {
            if (finishPathPercent >= 1)
            {
                increment = false;
            }
            else if (finishPathPercent <= 0)
            {
                increment = true;
            }

            return increment;
        }

        void setIncrement(bool increment) {
            EnemyMovement::increment = increment;
        }


        EnemyMovement():Component("EnemyMovement"){};


        void onAdded() override
        {
            finishPathPercent = 0;
            increment = 1;
            entity_transform = this->getEntity()->getComponent<Transform>();
            app = CGEngine::Application_Manager::getMainApp();

            if (!entity_transform)exit(-1);
            if (!app)exit(-1);

            initialize();
        }

        bool getIsHorizontal1() const {
            return isHorizontal;
        }

        void setIsHorizontal(bool isHorizontal) {
            EnemyMovement::isHorizontal = isHorizontal;
        }

        void initialize(){

            position_sensitivity = {3.0f, 3.0f, 3.0f};
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

            if(isHorizontal && position.x >= end.x) {
                increment = !increment;
            }

            else if(!isHorizontal && position.z >= end.z) {
                increment = !increment;
            }

            else if(isHorizontal && position.x <= start.x) {
                increment = !increment;
            }

            else if(!isHorizontal && position.z <= start.z) {
                increment = !increment;
            }

            if(isHorizontal && increment) {
                position += right * ((float)delta_time * current_sensitivity.x);
            }

            else if(isHorizontal && !increment)  {
                position -= right * ((float)delta_time * current_sensitivity.x);

            }

            else if(!isHorizontal && increment)  {
                position += front * ((float)delta_time * current_sensitivity.z);

            }

            else if(!isHorizontal && !increment)  {
                position -= front * ((float)delta_time * current_sensitivity.z);

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

    };

}

#endif //COMPUTER_GRAPHICS_PROJECT_ENEMY_MOVEMENT_H
