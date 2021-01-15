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


        void setEnd(const vec3 &end) {
            EnemyMovement::end = end;
        }


        float getFinishPathPercent() const {
            return finishPathPercent;
        }

        void setFinishPathPercent(float finishPathPercent) {
            EnemyMovement::finishPathPercent = finishPathPercent;
        }



        bool getIncrement() {

            return increment;
        }

        void setIncrement() {
            //EnemyMovement::increment = increment;
            if (finishPathPercent >= 1)
            {
                increment = false;
            }
            else if (finishPathPercent <= 0)
            {
                increment = true;
            }

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

            setIncrement();


            if(increment) {
                finishPathPercent += delta_time/current_sensitivity.x;
            }
            else if(!increment) {
                finishPathPercent -= delta_time/current_sensitivity.x;

            }
/*
            if(isHorizontal) {
                if(increment) {
                    entity_transform->rotate(0, delta_time * 200 /current_sensitivity.x, 0);
                }

                else if(!increment) {
                    entity_transform->rotate(0, -delta_time * 200 /current_sensitivity.x, 0);

                }


            }

            if(!isHorizontal) {
                if(increment) {
                    entity_transform->rotate(0, delta_time * 200 /current_sensitivity.x, 0);
                }

                else if(!increment) {
                    entity_transform->rotate(0, -delta_time * 200 /current_sensitivity.x, 0);

                }
            }
*/
            entity_transform->setPosition( glm::mix(start, end, finishPathPercent));
        }


        [[nodiscard]] glm::vec3 getPosition() const {return position;}


        [[nodiscard]] glm::vec3 getPositionSensitivity() const {return position_sensitivity;}
        [[nodiscard]] float getSpeedUpFactor() const {return speedup_factor;}


        void setPosition(glm::vec3 _pos) {
            this->position = _pos;
        }

        void setPositionSensitivity(glm::vec3 sensitivity){this->position_sensitivity = sensitivity;}

    };

}

#endif //COMPUTER_GRAPHICS_PROJECT_ENEMY_MOVEMENT_H
