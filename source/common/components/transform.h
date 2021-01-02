#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtx/matrix_decompose.hpp>
#include "ecs/component.h"
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <vector>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "unordered_map"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iomanip>


namespace CGEngine {

    enum class Space {
        World,
        Self
    };

    class Transform : public Component {

    protected:
        glm::vec3 position, scale;
        glm::quat rotation;

        int rootOrder = 0;

        int getRootOrder() const;

        void setRootOrder(int rootOrder);

        int indexNumber = 0;

    public:
        std::unordered_map<std::string, Transform *> children;
        Transform *parent = nullptr;


        glm::mat4 to_mat4() const {
            return glm::translate(glm::mat4(1.0f), position) *
                   glm::mat4_cast(rotation) *
                   glm::scale(glm::mat4(1.0f), scale);
        }
        void onAdded() override;



        Transform(glm::vec3 position = {0, 0, 0}, glm::quat rotation = {0, 0, 0, 0}, glm::vec3 scale = {1, 1, 1})
                : Component("transform"), position(position), rotation(rotation), scale(scale){}

        glm::mat4 getModelMatrix() const;

            //Matrix that transforms a point from local space into world space.
         glm::mat4 getLocalToWorldMatrix() const;

        //Matrix that transforms a point from world space into local space.
        const glm::mat4 getWorldToLocalMatrix() const;


        //Returns the position of the transform in world space.
        glm::vec3 getPosition() const;

        //Sets the position of the transform in world space.
        void setPosition(const glm::vec3 &position);

        //Sets the position of the transform in world space.
        void setPosition(const float x, const float y, const float z);

        //Returns the position of the transform relative to the parent transform.
        glm::vec3 getLocalPosition() const;

        //Sets the position of the transform relative to the parent transform.
        void setLocalPosition(const glm::vec3 &position);

        //Sets the position of the transform relative to the parent transform.
        void setLocalPosition(const float x, const float y, const float z);


        //Returns the scale of the transform relative to the parent transform(Read Only)..
        glm::vec3 getLossyScale() const;

        //Returns the scale of the transform relative to the parent transform.
        glm::vec3 getLocalScale() const;

        //Sets the scale of the transform relative to the parent transform.
        void setLocalScale(const glm::vec3 &scale);

        //Sets the scale of the transform relative to the parent transform.
        void setLocalScale(const float x, const float y, const float z);

        //Sets the scale of the transform relative to the parent transform.
        void setLocalScale(const float scale);

        //Returns the X axis of the transform in world space.
        glm::vec3 getRight() const;

        //Returns the Y axis of the transform in world space.
        glm::vec3 getUp() const;

        //Returns the Z axis of the transform in world space.
        glm::vec3 getForward() const;

        //TODO
        //Implement those two functions
        //Sets the X axis of the transform in world space.
        void setRight(const glm::vec3 &right);

        //Sets the Y axis of the transform in world space.
        void setUp(const glm::vec3 &up);

        //Sets the Z axis of the transform in world space.
        void setForward(const glm::vec3 &forward);

        //Rotates the transform so the forward vector points at worldPosition.
        void lookAt(const glm::vec3 &worldPosition, const glm::vec3 &worldUp = glm::vec3{0, 1, 0});

        //Rotates the transform so the forward vector points at /target/'s current position.
        void lookAt(const Transform &target, const glm::vec3 &worldUp = glm::vec3{0, 1, 0});

        //Returns the rotation as Euler angles in degrees.
        glm::vec3 getEulerAngles() const;

        //Sets the rotation as Euler angles in degrees.
        void setEulerAngles(const glm::vec3 eulerAngles);

        //Sets the rotation as Euler angles in degrees.
        void setEulerAngles(const float x, const float y, const float z);

        //Returns the rotation as Euler angles in degrees relative to the parent transform's rotation.
        glm::vec3 getLocalEulerAngles() const;

        //Sets the rotation as Euler angles in degrees relative to the parent transform's rotation.
        void setLocalEulerAngles(const glm::vec3 &eulerAngles);

        //Sets the rotation as Euler angles in degrees relative to the parent transform's rotation.
        void setLocalEulerAngles(const float x, const float y, const float z);

        //Returns the rotation of the transform in world space stored as a Quaternion.
        glm::quat getRotation() const;

        //Sets the rotation of the transform in world space stored as a Quaternion.
        void setRotation(const glm::quat &rotation);

        //Returns the rotation of the transform relative to the parent transform's rotation.
        glm::quat getLocalRotation() const;

        //Sets the rotation of the transform relative to the parent transform's rotation.
        void setLocalRotation(const glm::quat &rotation);

        //Moves the transform in the direction and distance of translation.
        void translate(glm::vec3 translation, Space relativeTo = Space::Self);

        //Rotates the transform in a variety of ways. The rotation is often provided as an Euler angle and not a Quaternion.
        void rotate(float xAngle, float yAngle, float zAngle, Space relativeTo = Space::Self);

        //Rotates the transform in a variety of ways. The rotation is often provided as an Euler angle and not a Quaternion.
        void rotate(glm::vec3 eulers, Space relativeTo = Space::Self);

        //Rotates the transform in a variety of ways. The rotation is often provided as an Euler angle and not a Quaternion.
        void rotate(glm::vec3 axis, float angle, Space relativeTo = Space::Self);

        //Rotates the transform about axis passing through point in world coordinates by angle degrees.
        void rotateAround(glm::vec3 point, glm::vec3 axis, float angle);

        //Transforms position from local space to world space.
        glm::vec3 transformPoint(const glm::vec3 &point) const;

        //Transforms vector from local space to world space.
        glm::vec3 transformVector(const glm::vec3 &direction) const;

        //Sets the world space position and rotation of the Transform component.
        void setPositionAndRotation(glm::vec3 position, glm::quat rotation);

        void updateMatrix() const;

        //Sets the parent of the transform.
        //parent: The parent Transform to use.
        //worldPositionStays: If true, the parent-relative position, scale and rotation are modified such that the object keeps the same world space position, rotation and scale as before.
        //Description
        void setParent(Transform* parent, bool worldPositionStays = true);

        //Returns the parent of the transform.
        Transform *getParent() const;

         //Returns the transform of children
         const std::unordered_map<std::string, Transform *> &getChildren() const;

        //Returns the transform of the child by name.
        Transform *getChild(const std::string name) const;

        //Returns the number of children the parent Transform has.
        int childCount() const;

        //TODO
        //Implement those two functions
        /*//Sets the sibling index.
        void setSiblingIndex(int index);

        //Gets the sibling index.
        int getSiblingIndex() const;

        //Sets the transform index.
        void setIndexNumber(int index);

        //Gets the transform index.
        int getIndexNumber() const;*/





    };
}
#endif //TRANSFORM_H
