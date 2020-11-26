#include "transform.h"
#include "ecs/scene.h"

//Returns the position of the transform in world space.
glm::vec3 CGEngine::Transform::getPosition() const {

    glm::mat4 localToWorldMatrix = getLocalToWorldMatrix();
    return glm::vec3(localToWorldMatrix[0][3], localToWorldMatrix[1][3], localToWorldMatrix[2][3]);
}

//Sets the position of the transform in world space.
void CGEngine::Transform::setPosition(const glm::vec3 &position) {
    setPosition(position.x, position.y, position.z);
}

//Sets the position of the transform in world space.
void CGEngine::Transform::setPosition(const float x, const float y, const float z) {
    if (parent != nullptr) {
        glm::mat4 parentMat = parent->getWorldToLocalMatrix();
        glm::vec4 temp = parentMat * glm::vec4(x, y, z, 0);
        position = glm::vec3(temp.x, temp.y, temp.z);
    } else {
        position = glm::vec3(x, y, z);
    }
}

//Returns the position of the transform relative to the parent transform.
glm::vec3 CGEngine::Transform::getLocalPosition() const {
    return position;
}

//Sets the position of the transform relative to the parent transform.
void CGEngine::Transform::setLocalPosition(const glm::vec3 &position) {
    this->position = position;
}

//Sets the position of the transform relative to the parent transform.
void CGEngine::Transform::setLocalPosition(const float x, const float y, const float z) {
    position = glm::vec3(x, y, z);
}

//Returns the scale of the transform relative to the parent transform(Read Only)..
glm::vec3 CGEngine::Transform::getLossyScale() const {
    if (parent != nullptr) {
        glm::vec3 parenVector = parent->getLossyScale();
        return glm::vec3(scale.x * parenVector.x, scale.y * parenVector.y, scale.z * parenVector.z);
    }
    return scale;
}

//Returns the scale of the transform relative to the parent transform.
glm::vec3 CGEngine::Transform::getLocalScale() const {
    return scale;

}

//Sets the scale of the transform relative to the parent transform.
void CGEngine::Transform::setLocalScale(const glm::vec3 &scale) {
    this->scale = scale;
}

//Sets the scale of the transform relative to the parent transform.
void CGEngine::Transform::setLocalScale(const float x, const float y, const float z) {
    scale = glm::vec3(x, y, z);
}

//Sets the scale of the transform relative to the parent transform.
void CGEngine::Transform::setLocalScale(const float scale) {
    setLocalScale(scale, scale, scale);
}

//Matrix that transforms a point from local space into world space.
const glm::mat4 &CGEngine::Transform::getLocalToWorldMatrix() const {
    glm::mat4 mat = glm::transpose(to_mat4());
    if (parent != nullptr) {
        glm::mat4 matParent = parent->getLocalToWorldMatrix();
        mat = matParent * mat;
    }
    return mat;
}

//Matrix that transforms a point from world space into local space.
const glm::mat4 &CGEngine::Transform::getWorldToLocalMatrix() const {

    glm::mat4 temp = getLocalToWorldMatrix();
    glm::mat4 mat = glm::inverse(temp);
    return mat;
}

//Returns the X axis of the transform in world space.
glm::vec3 CGEngine::Transform::getRight() const {
    glm::mat4 mat = getLocalToWorldMatrix();
    return {mat[0][0],mat[1][0],mat[2][0]};
    //return getRotation() * glm::vec3(1, 0, 0);
}

//Returns the Y axis of the transform in world space.
glm::vec3 CGEngine::Transform::getUp() const {
    glm::mat4 mat = getLocalToWorldMatrix();
    return {mat[0][1],mat[1][1],mat[2][1]};
    //return getRotation() * glm::vec3(0, 1, 0);
}

//Returns the Z axis of the transform in world space.
glm::vec3 CGEngine::Transform::getForward() const {
    glm::mat4 mat = getLocalToWorldMatrix();
    return {mat[0][2],mat[1][2],mat[2][2]};
    //return getRotation() * glm::vec3(0, 0, 1);
}

//Sets the Z axis of the transform in world space.
void CGEngine::Transform::setForward(const glm::vec3 &forward) {
    glm::vec3 upVector = this->getUp();
    glm::vec3 upNew = glm::normalize(upVector);
    glm::vec3 forwardNew = glm::normalize(forward);
    glm::quat qua=glm::quatLookAt(-forwardNew, upNew);
    this->setRotation(qua);
}

//Sets the X axis of the transform in world space.
void CGEngine::Transform::setRight(const glm::vec3 &right)
{
    /*glm::vec3 upVector = this->getUp();
    glm::vec3 upNew = glm::normalize(upVector);
    glm::vec3 forwardNew = glm::normalize(forward);
    glm::quat qua=glm::quatLookAt(-forwardNew, upNew);
    this->setRotation(qua);*/
}

//Sets the Y axis of the transform in world space.
void CGEngine::Transform::setUp(const glm::vec3 &up)
{
    glm::vec3 upVector = this->getUp();
    glm::vec3 upNew = glm::normalize(up);
    glm::vec3 forwardNew = glm::normalize(getForward());
    glm::quat qua=glm::quatLookAt(upNew, forwardNew);
    this->setRotation(qua);

}

//Returns the rotation of the transform in world space stored as a Quaternion.
glm::quat CGEngine::Transform::getRotation() const {
    glm::quat vec = glm::quat_cast(getLocalToWorldMatrix());
    return vec;
}

//Sets the rotation of the transform in world space stored as a Quaternion.
void CGEngine::Transform::setRotation(const glm::quat &rotation) {
    if (parent != nullptr) {
        this->rotation = glm::inverse(glm::quat(parent->getRotation())) * rotation;
    } else {
        this->rotation = rotation;

    }
}

//Returns the rotation as Euler angles in degrees.
glm::vec3 CGEngine::Transform::getEulerAngles() const {
    return glm::degrees(glm::eulerAngles(getRotation()));
}

//Sets the rotation as Euler angles in degrees.
void CGEngine::Transform::setEulerAngles(const glm::vec3 eulerAngles) {
    glm::quat quaternion = glm::quat(glm::radians(glm::vec3(eulerAngles.x, eulerAngles.y, eulerAngles.z)));
    setRotation(quaternion);
}

//Sets the rotation as Euler angles in degrees.
void CGEngine::Transform::setEulerAngles(const float x, const float y, const float z) {
    glm::quat quaternion = glm::quat(glm::radians(glm::vec3(x, y, z)));
    setRotation(quaternion);
}

//Returns the rotation of the transform relative to the parent transform's rotation.
glm::quat CGEngine::Transform::getLocalRotation() const {
    return rotation;
}

//Sets the rotation of the transform relative to the parent transform's rotation.
void CGEngine::Transform::setLocalRotation(const glm::quat &rotation) {
    this->rotation = rotation;
}

//Returns the rotation as Euler angles in degrees relative to the parent transform's rotation.
glm::vec3 CGEngine::Transform::getLocalEulerAngles() const {
    return glm::degrees(glm::eulerAngles(rotation));
}

//Sets the rotation as Euler angles in degrees relative to the parent transform's rotation.
void CGEngine::Transform::setLocalEulerAngles(const glm::vec3 &eulerAngles) {
    this->rotation = glm::quat(glm::radians(glm::vec3(eulerAngles.x, eulerAngles.y, eulerAngles.z)));

}

//Sets the rotation as Euler angles in degrees relative to the parent transform's rotation.
void CGEngine::Transform::setLocalEulerAngles(const float x, const float y, const float z) {
    this->rotation = glm::quat(glm::radians(glm::vec3(x, y, z)));

}

//Moves the transform in the direction and distance of translation.
void CGEngine::Transform::translate(glm::vec3 translation, Space relativeTo) {
    if (relativeTo == Space::World) {
        setPosition(getPosition() + translation);
    } else {
        setLocalPosition(position + translation);
    }
}

//Rotates the transform in a variety of ways. The rotation is often provided as an Euler angle and not a Quaternion.
void CGEngine::Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo) {
    glm::mat4 rotationMatrix = glm::rotate(glm::radians(xAngle), glm::vec3(1, 0, 0));
    glm::mat4 temp1=glm::rotate(glm::radians(yAngle), glm::vec3(0, 1, 0));
    glm::mat4 temp2=glm::rotate(glm::radians(zAngle), glm::vec3(0, 0, 1));
    rotationMatrix *= temp1;
    rotationMatrix *= temp2;
    //glm::quat quaternion = glm::quat(glm::radians(glm::vec3(xAngle, yAngle, zAngle)));
    //glm::mat4 rotationMatrix =glm::mat4_cast(quaternion);
    /*glm::mat4 model_mat = glm::transpose(to_mat4());
    model_mat = glm::rotate(model_mat,glm::radians(xAngle),glm::vec3(1,0,0));
    model_mat = glm::rotate(model_mat,glm::radians(yAngle),glm::vec3(0,1,0));
    model_mat = glm::rotate(model_mat,glm::radians(zAngle),glm::vec3(0,0,1));*/

    glm::mat4 model_mat = glm::transpose(to_mat4());
    glm::mat4 localToWorldMatrix = this->getLocalToWorldMatrix();
    if (relativeTo == Space::World) {
        glm::mat4 temp = rotationMatrix * localToWorldMatrix;
        setRotation(glm::quat_cast(temp));
    } else {
        glm::mat4 temp = localToWorldMatrix * rotationMatrix;
        setLocalRotation(glm::quat_cast(temp));
        position.x=temp[0][3];
        position.y=temp[1][3];
        position.z=temp[2][3];
    }

}

//Rotates the transform in a variety of ways. The rotation is often provided as an Euler angle and not a Quaternion.
void CGEngine::Transform::rotate(glm::vec3 eulers, Space relativeTo) {
    rotate(eulers.x, eulers.y, eulers.z, relativeTo);
}

//Rotates the transform in a variety of ways. The rotation is often provided as an Euler angle and not a Quaternion.
void CGEngine::Transform::rotate(glm::vec3 axis, float angle, Space relativeTo) {

    //glm::quat temp = glm::angleAxis(glm::radians(angle),axis);
    glm::mat4 localToWorldMatrix = this->getLocalToWorldMatrix();
    glm::mat4 model_mat = glm::transpose(to_mat4());
    glm::mat4 new_model_matrix = glm::rotate(model_mat,glm::radians(angle),axis);

    if (relativeTo == Space::World) {
        glm::mat4 temp = new_model_matrix * localToWorldMatrix;
        setRotation(glm::quat_cast(temp));
    } else {
        glm::mat4 temp = localToWorldMatrix * new_model_matrix;
        setLocalRotation(glm::quat_cast(temp));
        position.x=temp[0][3];
        position.y=temp[1][3];
        position.z=temp[2][3];
    }

}

//Rotates the transform about axis passing through point in world coordinates by angle degrees.
void CGEngine::Transform::rotateAround(glm::vec3 point, glm::vec3 axis, float angle) {
    glm::vec3 axisNew = glm::normalize(axis);
    glm::quat new_quat = glm::angleAxis(angle,axis);
   // glm::rotate(point,angle,Space::World);
    // step1: update position
    glm::vec3 vector = this->getPosition();
    glm::quat rotation = glm::angleAxis(angle, axis);
    glm::vec3 vector2 = vector - point;
    vector2 = rotation * vector2;
    vector = point + vector2;
    setPosition(vector);

    // step2: update rotation
    rotation = rotation * rotation;
    //RotateAroundInternal(axis, angle);
    //MakeDirty();
}

//Rotates the transform so the forward vector points at worldPosition.
void CGEngine::Transform::lookAt(const glm::vec3 &worldPosition, const glm::vec3 &worldUp) {
    glm::vec3 directionNew = glm::normalize(worldPosition);
    glm::vec3 upNew = glm::normalize(worldUp);

    this->setRotation(glm::quatLookAt(directionNew, upNew));
}

//Rotates the transform so the forward vector points at /target/'s current position.
void CGEngine::Transform::lookAt(const Transform& target, const glm::vec3 &worldUp)
{
    glm::vec3 directionNew = glm::normalize(target.position);
    glm::vec3 upNew = glm::normalize(worldUp);
    this->setRotation(glm::quatLookAt(directionNew, upNew));
}
//Transforms position from local space to world space.
glm::vec3 CGEngine::Transform::transformPoint(const glm::vec3 &point) const {
    glm::mat4 mat = getLocalToWorldMatrix();
    glm::vec4 my_point = glm::vec4 (point.x,point.y,point.z,1);
    glm::vec4 result = mat * my_point;
    glm::vec3 temp = glm::vec3 (result.x,result.y,result.z);
    return temp;
}

//Transforms direction from local space to world space.
glm::vec3 CGEngine::Transform::transformDirection(const glm::vec3 &direction) const {
    glm::mat4 mat = getLocalToWorldMatrix();
    glm::vec4 my_direction = glm::vec4 (direction.x,direction.y,direction.z,0);
    glm::vec4 result = mat * my_direction;
    glm::vec3 temp = glm::vec3 (result.x,result.y,result.z);
    return temp;
}

//Transforms vector from local space to world space.
glm::vec3 CGEngine::Transform::transformVector(const glm::vec3 &direction) const {
    glm::mat4 mat = getLocalToWorldMatrix();
    glm::vec4 my_direction = glm::vec4 (direction.x,direction.y,direction.z,0);
    glm::vec4 result = mat * my_direction;
    glm::vec3 temp = glm::vec3 (result.x,result.y,result.z);
    return temp;
}

//Sets the world space position and rotation of the Transform component.
void CGEngine::Transform::setPositionAndRotation(glm::vec3 position, glm::quat rotation) {
    setPosition(position);
    setRotation(rotation);
}
/*
void CGEngine::Transform::updateMatrix() const {
}
*/
//Sets the parent of the transform.
//parent: The parent Transform to use.
//worldPositionStays: If true, the parent-relative position, scale and rotation are modified such that the object keeps the same world space position, rotation and scale as before.
//Description
void CGEngine::Transform::setParent(Transform *parent, bool worldPositionStays) {

    Transform *old_parent = this->parent;
    //Check if the old parent is the same as the new parent
    if (parent == old_parent) {
        return;
    }
    //Check if the new parent equals to nullptr then the current transform will be a root transform
    if (parent == nullptr) {
        Scene *scene = this->entity->getScene();
        scene->addRootTransform(this);
    }
        //Check if the old parent equals to nullptr then the current transform will be removed from the root transforms
    else if (old_parent == nullptr) {
        Scene *scene = this->entity->getScene();
        scene->removeRootTransform(this);
    }

    // New parent can not be child of this transform
    Transform *p = parent;
    while (p != nullptr) {
        if (p == this) {
            puts("New parent can not be child of this transform");
            return;
        }
        p = p->getParent();
    }


    // Remove from old parent
    if (old_parent != nullptr) {
        // TODO: remove first, not remove all
        //			old_parent->m_children.erase(old_parent->m_children.begin()+m_RootOrder);
        std::remove(old_parent->children.begin(), old_parent->children.end(), this);
    }

    this->parent = parent;
    if (parent != nullptr) {
        parent->children.push_back(this);
        rootOrder = (int) parent->children.size() - 1;
    }

    if (worldPositionStays) {
        //glm::mat4 mat = Matrix4x4::TRS(m_LocalPosition, m_LocalRotation, m_LocalScale);
        glm::mat4 mat = glm::transpose(to_mat4());

        if (old_parent != nullptr) {
            glm::mat4 parentMat = old_parent->getLocalToWorldMatrix();
            mat = parentMat * mat;
        }
        if (parent != nullptr) {
            glm::mat4 parentMat = parent->getWorldToLocalMatrix();
            mat = parentMat * mat;
        }
        glm::vec3 skew(0);
        glm::vec4 perspective(0);
        glm::decompose(mat, scale, rotation, position, skew, perspective);
        rotation = glm::conjugate(rotation);

        position.x=mat[0][3];
        position.y=mat[1][3];
        position.z=mat[2][3];
        rotation = glm::quat_cast(mat);

    }
    //UpdateMatrix();
    //MakeDirty();
}

int CGEngine::Transform::getRootOrder() const {
    return rootOrder;
}

void CGEngine::Transform::setRootOrder(int rootOrder) {
    Transform::rootOrder = rootOrder;
}

//Returns the parent of the transform.
CGEngine::Transform *CGEngine::Transform::getParent() const {
    return this->parent;
}

//Returns the transform of children
const std::vector<CGEngine::Transform *> &CGEngine::Transform::getChildren() const {
    return children;
}

//Returns the transform of the child by index.
CGEngine::Transform *CGEngine::Transform::getChild(int index) const {
    return children[index];
}

//Returns the number of children the parent Transform has.
int CGEngine::Transform::childCount() {
    return children.size();
}
