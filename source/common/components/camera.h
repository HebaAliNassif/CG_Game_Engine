#ifndef CAMERA_H
#define CAMERA_H

#include <application_manager.h>
#include "ecs/component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <entity.h>
#include <iostream>
#include <iomanip>
#include <glm/vector_relational.hpp>
#include <transform.h>

namespace CGEngine {

    // An enum for the camera projection type
    enum struct CameraType {
        Orthographic,
        Perspective
    };

    // A class that represents a camera
    // Used to generate a view and a projection matrix
    class Camera : public Component {
    private:
        // Dirty Flags are programming pattern where we only regenerate some output if:
        // 1- The inputs were changed.
        // 2- The output is needed.
        // Where we have flags for whether the View, Projection & ViewProjection matrices needed to be regenerated.
        static const uint8_t V_DIRTY = 1, P_DIRTY = 2, VP_DIRTY = 4;
        uint8_t dirtyFlags = 0;

        CameraType type = CameraType::Perspective;

        // The field_of_view_y is in radians and is only used for perspective cameras
        // The orthographic_height is only used for orthographic cameras
        float field_of_view_y = glm::radians(
                90.0f), orthographic_height = 2.0f, aspect_ratio = 1.0f, near = 0.01f, far = 100.0f;

        glm::mat4 V{}, P{}, VP{};
        float fov_sensitivity = glm::pi<float>()/10;


    protected:

    public:

        //Reference to the transform component of the camera.
        Transform *camera_transform = nullptr;
        bool scroll = true;


        Camera() : Component("camera") {
            dirtyFlags = V_DIRTY | P_DIRTY | VP_DIRTY;
        }

        void onAdded() override {
            if (!camera_transform)camera_transform = this->getEntity()->getComponent<Transform>();
            Application_Manager *app = CGEngine::Application_Manager::getMainApp();
            int width, height;
            glfwGetFramebufferSize(app->getWindow(), &width, &height);
            this->setupPerspective(glm::pi<float>() / 2, static_cast<float>(width) / height, 0.1f, 100.0f);
        }

        void update(double delta_time) override
        {
            if(scroll==true) {
                float fov = this->getVerticalFieldOfView() +
                            CGEngine::Application_Manager::getMainApp()->getMouse().getScrollOffset().y *
                            fov_sensitivity;
                fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f);
                this->setVerticalFieldOfView(fov);
            }
        }

        // Setup the camera as a perspective camera
        void setupPerspective(float field_of_view_y, float aspect_ratio, float near, float far) {
            this->type = CameraType::Perspective;
            this->field_of_view_y = field_of_view_y;
            this->aspect_ratio = aspect_ratio;
            this->near = near;
            this->far = far;
            dirtyFlags |= P_DIRTY | VP_DIRTY; // Both P & VP need to be regenerated
        }

        // Setup the camera as an orthographic camera
        void setupOrthographic(float orthographic_height, float aspect_ratio, float near, float far) {
            this->type = CameraType::Orthographic;
            this->orthographic_height = orthographic_height;
            this->aspect_ratio = aspect_ratio;
            this->near = near;
            this->far = far;
            dirtyFlags |= P_DIRTY | VP_DIRTY; // Both P & VP need to be regenerated
        }

        void setType(CameraType _type) {
            if (this->type != _type) {
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->type = _type;
            }
        }

        void setOrthographicSize(float orthographic_height) {
            if (this->orthographic_height != orthographic_height) {
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->orthographic_height = orthographic_height;
            }
        }

        void setVerticalFieldOfView(float field_of_view_y) {
            if (this->field_of_view_y != field_of_view_y) {
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->field_of_view_y = field_of_view_y;
            }
        }

        void setAspectRatio(float aspect_ratio) {
            if (this->aspect_ratio != aspect_ratio) {
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->aspect_ratio = aspect_ratio;
            }
        }

        void setNearPlane(float near) {
            if (this->near != near) {
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->near = near;
            }
        }

        void setFarPlane(float far) {
            if (this->far != far) {
                dirtyFlags |= P_DIRTY | VP_DIRTY;
                this->far = far;
            }
        }

        void setEyePosition(glm::vec3 eye) {
            if (camera_transform->getPosition() != eye) {
                dirtyFlags |= V_DIRTY | VP_DIRTY;
                camera_transform->setPosition(eye);
            }

        }

        void setDirection(float y, float p, float r) {
            glm::vec3 direction = (glm::vec3(glm::cos(y), 0, -glm::sin(y)) * glm::cos(p) +
                                   glm::vec3(0, glm::sin(p), 0));
            if (!glm::all(glm::equal(camera_transform->getForward(), direction))) {
                dirtyFlags |= V_DIRTY | VP_DIRTY;
                camera_transform->setEulerAngles(p, y, r);
            }
        }

        void setTarget(glm::vec3 target) {
            glm::vec3 direction = target - camera_transform->getPosition();
            if (camera_transform->getForward() != direction) {
                dirtyFlags |= V_DIRTY | VP_DIRTY;
                camera_transform->setForward(direction);
            }
        }

        glm::mat4 getProjectionMatrix() {
            if (dirtyFlags & P_DIRTY) { // Only regenerate the projection matrix if its flag is dirty
                if (type == CameraType::Orthographic) {
                    float half_height = orthographic_height * 0.5f;
                    float half_width = aspect_ratio * half_height;
                    P = glm::ortho(-half_width, half_width, -half_height, half_height, near, far);
                } else {
                    P = glm::perspective(field_of_view_y, aspect_ratio, near, far);
                }
                dirtyFlags &= ~P_DIRTY; // P is no longer dirty
            }
            return P;
        }

        glm::mat4 getViewMatrix() {
            V = camera_transform->getWorldToLocalMatrix();

            if (dirtyFlags & V_DIRTY) { // Only regenerate the view matrix if its flag is dirty
                V = camera_transform->getWorldToLocalMatrix();
                dirtyFlags &= ~V_DIRTY; // V is no longer dirty
            }
            return V;
        }

        glm::mat4 getVPMatrix() {
            VP = getProjectionMatrix() * getViewMatrix();
            if (dirtyFlags & VP_DIRTY) {
                // Note that we called the functions getProjectionMatrix & getViewMatrix instead of directly using V & P
                // to make sure that they are not outdated
                dirtyFlags = 0; // Nothing is dirty anymore
            }
            return VP;
        }

        CameraType getType() { return type; }

        [[nodiscard]] float getVerticalFieldOfView() const { return field_of_view_y; }

        [[nodiscard]] float getHorizontalFieldOfView() const { return field_of_view_y * aspect_ratio; }

        [[nodiscard]] float getOrthographicHeight() const { return orthographic_height; }

        [[nodiscard]] float getOrthographicWidth() const { return orthographic_height * aspect_ratio; }

        [[nodiscard]] float getAspectRatio() const { return aspect_ratio; }

        [[nodiscard]] float getNearPlane() const { return near; }

        [[nodiscard]] float getFarPlane() const { return far; }

        [[nodiscard]] glm::vec3 getEyePosition() const { return camera_transform->getLocalPosition(); }

        [[nodiscard]] glm::vec3 getDirection() const { return (camera_transform->getForward()); }

        [[nodiscard]] glm::vec3 getOriginalUp() const { return camera_transform->getUp(); }

        // Get the directions of the camera coordinates in the world space
        glm::vec3 Right() {
            return camera_transform->getRight();
        }

        glm::vec3 Left() {
            return -camera_transform->getRight();
        }

        glm::vec3 Up() {
            return camera_transform->getUp();
        }

        glm::vec3 Down() {
            return -camera_transform->getUp();
        }

        glm::vec3 Forward() {
            return camera_transform->getForward();
        }

        glm::vec3 Backward() {
            return -camera_transform->getForward();
        }

        // Transform point from world space to normalized device coordinates
        glm::vec3 fromWorldToDeviceSpace(glm::vec3 world) {
            glm::vec4 clip = getVPMatrix() * glm::vec4(world, 1.0f);
            return glm::vec3(clip) / clip.w;
            // Note that we must divide by w. This is because of the projection matrix.
        }

        // Transform point from normalized device coordinates to world space
        glm::vec3 fromDeviceToWorldSpace(glm::vec3 device) {
            glm::vec4 clip = glm::inverse(getVPMatrix()) * glm::vec4(device, 1.0f);
            return glm::vec3(clip) / clip.w;
            // Note that we must divide by w even though we not going to the NDC space. This is because of the projection matrix.
        }

    };

}
#endif //CAMERA_H