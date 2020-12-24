#include "transform.h"
#include "ecs/scene.h"
#include "quaternion_utils.h"
#include "glm/gtx/string_cast.hpp"

void PrintMat4x4mm(glm::mat4 mat)
{
    std::cout<<std::setw(20)<<mat[0][0]<<std::setw(20)<<mat[0][1]<<std::setw(20)<<mat[0][2]<<std::setw(20)<<mat[0][3]<<std::setw(20)<<"\n";
    std::cout<<std::setw(20)<<mat[1][0]<<std::setw(20)<<mat[1][1]<<std::setw(20)<<mat[1][2]<<std::setw(20)<<mat[1][3]<<std::setw(20)<<"\n";
    std::cout<<std::setw(20)<<mat[2][0]<<std::setw(20)<<mat[2][1]<<std::setw(20)<<mat[2][2]<<std::setw(20)<<mat[2][3]<<std::setw(20)<<"\n";
    std::cout<<std::setw(20)<<mat[3][0]<<std::setw(20)<<mat[3][1]<<std::setw(20)<<mat[3][2]<<std::setw(20)<<mat[3][3]<<std::setw(20)<<"\n";
}
void CGEngine::Transform::onAdded()
{
    this->scene->addRootTransform(this);
}

glm::vec3 CGEngine::Transform::getPosition() const {

    glm::mat4 localToWorldMatrix = getLocalToWorldMatrix();
    return glm::vec3(localToWorldMatrix[3][0], localToWorldMatrix[3][1], localToWorldMatrix[3][2]);
}

void CGEngine::Transform::setPosition(const glm::vec3 &position) {
    setPosition(position.x, position.y, position.z);
}

void CGEngine::Transform::setPosition(const float x, const float y, const float z) {

    if (parent != nullptr) {
        glm::mat4 parentMat = parent->getWorldToLocalMatrix();
        glm::vec4 temp = parentMat * glm::vec4(x, y, z, 0);
        position = glm::vec3(temp.x, temp.y, temp.z);
    } else {
        position = glm::vec3(x, y, z);
    }
}

glm::vec3 CGEngine::Transform::getLocalPosition() const {
    return position;
}

void CGEngine::Transform::setLocalPosition(const glm::vec3 &position) {
    this->position = position;
}

void CGEngine::Transform::setLocalPosition(const float x, const float y, const float z) {
    position = glm::vec3(x, y, z);
}

glm::vec3 CGEngine::Transform::getLossyScale() const {
    if (parent != nullptr) {
        glm::vec3 parenVector = parent->getLossyScale();
        return glm::vec3(scale.x * parenVector.x, scale.y * parenVector.y, scale.z * parenVector.z);
    }
    return scale;
}

glm::vec3 CGEngine::Transform::getLocalScale() const {
    return scale;

}

void CGEngine::Transform::setLocalScale(const glm::vec3 &scale) {
    this->scale = scale;
}

void CGEngine::Transform::setLocalScale(const float x, const float y, const float z) {
    scale = glm::vec3(x, y, z);
}

void CGEngine::Transform::setLocalScale(const float scale) {
    setLocalScale(scale, scale, scale);
}

const glm::mat4 CGEngine::Transform::getLocalToWorldMatrix() const {

    glm::mat4 ModelMatrix = getModelMatrix();

    if (parent != nullptr) {
        glm::mat4 matParent = parent->getLocalToWorldMatrix();
        ModelMatrix = matParent * ModelMatrix;
    }
    return ModelMatrix;
}

glm::mat4 CGEngine::Transform::getModelMatrix() const {
    glm::mat4 RotationMatrix = glm::mat4_cast(this->rotation);
    glm::mat4 TranslationMatrix =glm::translate(glm::mat4(1.0f), this->position);
    glm::mat4 ScalingMatrix = glm::scale(glm::mat4(1.0f), this->scale);
    glm::mat4 ModelMatrix =  TranslationMatrix* RotationMatrix *ScalingMatrix;
    return ModelMatrix;
}

const glm::mat4 CGEngine::Transform::getWorldToLocalMatrix() const {

    glm::mat4 temp = getLocalToWorldMatrix();
    glm::mat4 mat = glm::inverse(temp);
    return mat;
}

glm::vec3 CGEngine::Transform::getRight() const {
    glm::mat4 mat = getWorldToLocalMatrix();
    glm::vec3 res = glm::normalize(glm::vec3 (mat[0][0],mat[1][0],mat[2][0]));
    return res;
}

glm::vec3 CGEngine::Transform::getUp() const {
    glm::mat4 mat = getWorldToLocalMatrix();
    glm::vec3 res = glm::normalize(glm::vec3 (mat[0][1],mat[1][1],mat[2][1]));
    return res;
}

glm::vec3 CGEngine::Transform::getForward() const {
    glm::mat4 mat = getWorldToLocalMatrix();
    glm::vec3 res = glm::normalize(-glm::vec3 (mat[0][2],mat[1][2],mat[2][2]));
    return res;
}

void CGEngine::Transform::setForward(const glm::vec3 &forward) {
    glm::vec3 direction = forward - this->getPosition();
    glm::quat qua = glm::quatLookAt(glm::normalize(direction), glm::normalize(this->getUp()));
    this->setRotation(qua);
}

glm::quat CGEngine::Transform::getRotation() const {
    glm::quat vec = glm::quat_cast(getLocalToWorldMatrix());
    return vec;
}

void CGEngine::Transform::setRotation(const glm::quat &rotation) {
    if (parent != nullptr) {
        glm::mat4 parentMat = parent->getWorldToLocalMatrix();
        glm::mat4 temp = parentMat * glm::mat4_cast(glm::quat(parent->getRotation()));
        this->rotation = glm::quat_cast(temp);

    } else {
        this->rotation = rotation;

    }
}

glm::vec3 CGEngine::Transform::getEulerAngles() const {
    return glm::degrees(glm::eulerAngles(getRotation()));
}

void CGEngine::Transform::setEulerAngles(const glm::vec3 eulerAngles) {
    setEulerAngles(eulerAngles.x,eulerAngles.y,eulerAngles.z);
}

void CGEngine::Transform::setEulerAngles(const float x, const float y, const float z) {
    glm::quat qua = glm::quat_cast(glm::yawPitchRoll(glm::radians(y), glm::radians(x) ,glm::radians(z)));
    this->setRotation(qua);
}

glm::quat CGEngine::Transform::getLocalRotation() const {
    return rotation;
}

void CGEngine::Transform::setLocalRotation(const glm::quat &rotation) {
    this->rotation = rotation;
}

glm::vec3 CGEngine::Transform::getLocalEulerAngles() const {
    return glm::degrees(glm::eulerAngles(rotation));
}

void CGEngine::Transform::setLocalEulerAngles(const glm::vec3 &eulerAngles) {
    setLocalEulerAngles(eulerAngles.x, eulerAngles.y, eulerAngles.z);

}

void CGEngine::Transform::setLocalEulerAngles(const float x, const float y, const float z) {
    this->rotation = glm::quat(glm::radians(glm::vec3(x, y, z)));

}

void CGEngine::Transform::translate(glm::vec3 translation, Space relativeTo) {
    if (relativeTo == Space::World) {
        setPosition(getPosition() + translation);
    } else {
        setLocalPosition(position + translation);
    }
}

void CGEngine::Transform::rotate(float xAngle, float yAngle, float zAngle, Space relativeTo) {

    glm::vec3 EulerAngles(glm::radians(xAngle), glm::radians(yAngle), glm::radians(zAngle));
    glm::quat MyQuaternion = glm::quat(EulerAngles);
    glm::mat4 rotationMatrix = glm::mat4_cast(MyQuaternion);

    glm::mat4 localToWorldMatrix = this->getLocalToWorldMatrix();

    glm::mat4 temp =   rotationMatrix * localToWorldMatrix ;
    setLocalRotation(glm::quat_cast(temp));
}

void CGEngine::Transform::rotate(glm::vec3 eulers, Space relativeTo) {
    rotate(eulers.x, eulers.y, eulers.z, relativeTo);
}

void CGEngine::Transform::rotate(glm::vec3 axis, float angle, Space relativeTo) {

    glm::mat4 localToWorldMatrix = this->getLocalToWorldMatrix();
    glm::mat4 model_mat = glm::transpose(to_mat4());
    glm::mat4 new_model_matrix = glm::rotate(model_mat,glm::radians(angle),axis);

    if (relativeTo == Space::World) {
        glm::mat4 temp = new_model_matrix * localToWorldMatrix;
        setRotation(glm::quat_cast(temp));
    } else {
        glm::mat4 temp = localToWorldMatrix * new_model_matrix;
        setLocalRotation(glm::quat_cast(temp));
        position.x=temp[3][0];
        position.y=temp[3][1];
        position.z=temp[3][2];
    }

}

void CGEngine::Transform::rotateAround(glm::vec3 point, glm::vec3 axis, float angle) {
    glm::vec3 axisNormal = glm::normalize(axis);
    glm::vec3 vector = this->getPosition();
    glm::quat rotation = glm::angleAxis(angle, axisNormal);
    glm::vec3 vector2 = vector - point;
    vector2 = rotation * vector2;
    vector = point + vector2;

    setPosition(vector);
    this->rotation = rotation * this->rotation;

}

void CGEngine::Transform::lookAt(const glm::vec3 &worldPosition, const glm::vec3 &worldUp) {
    glm::vec3 directionNew = glm::normalize(worldPosition);
    glm::vec3 upNew = glm::normalize(worldUp);
    this->setRotation(glm::quatLookAt(directionNew, upNew));
}

void CGEngine::Transform::lookAt(const Transform& target, const glm::vec3 &worldUp)
{
    glm::vec3 directionNew = glm::normalize(target.position);
    glm::vec3 upNew = glm::normalize(worldUp);
    this->setRotation(glm::quatLookAt(directionNew, upNew));
}

glm::vec3 CGEngine::Transform::transformPoint(const glm::vec3 &point) const {
    glm::mat4 mat = getLocalToWorldMatrix();
    glm::vec4 my_point = glm::vec4 (point.x,point.y,point.z,1);
    glm::vec4 result = mat * my_point;
    glm::vec3 temp = glm::vec3 (result.x,result.y,result.z);
    return temp;
}

glm::vec3 CGEngine::Transform::transformVector(const glm::vec3 &direction) const {
    glm::mat4 mat = getLocalToWorldMatrix();
    glm::vec4 my_direction = glm::vec4 (direction.x,direction.y,direction.z,0);
    glm::vec4 result = mat * my_direction;
    glm::vec3 temp = glm::vec3 (result.x,result.y,result.z);
    return temp;
}

void CGEngine::Transform::setPositionAndRotation(glm::vec3 position, glm::quat rotation) {
    setPosition(position);
    setRotation(rotation);
}

void CGEngine::Transform::setParent(Transform* parent, bool worldPositionStays) {

    Transform* old_parent = this->parent;

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

        std::unordered_map<std::string, Transform*>::iterator it = old_parent->children.begin();
        while(it != old_parent->children.end())
        {
            if(it->second == this)
                break;
            it++;
        }
        if (it != old_parent->children.end())
            old_parent->children.erase(it);

    }


    this->parent = parent;
    if (parent != nullptr) {
        parent->children[this->entity->name]=this;
        rootOrder = (int) parent->children.size() - 1;
    }

    if (worldPositionStays) {

        glm::mat4 ModelMarix = getModelMatrix();

        if (old_parent != nullptr) {
            glm::mat4 parentMat = old_parent->getLocalToWorldMatrix();
            ModelMarix = parentMat * ModelMarix;
        }
        if (parent != nullptr) {
            glm::mat4 parentMat = parent->getWorldToLocalMatrix();
            ModelMarix =   parentMat * ModelMarix  ;
        }
        position.x=ModelMarix[3][0];
        position.y=ModelMarix[3][1];
        position.z=ModelMarix[3][2];
        rotation = glm::quat_cast(ModelMarix);
    }

}

int CGEngine::Transform::getRootOrder() const {
    return rootOrder;
}

CGEngine::Transform *CGEngine::Transform::getParent() const {
    return this->parent;
}

const  std::unordered_map<std::string, CGEngine::Transform *> &CGEngine::Transform::getChildren() const {
    return children;
}

CGEngine::Transform *CGEngine::Transform::getChild(const std::string name) const {
    if(children.find(name)==children.end())return nullptr;
   return children.at(name);
}

int CGEngine::Transform::childCount() const {

    return children.size();
}
std::string vector3ToSting(glm::vec3 vector)
{
    std::string s = "["+std::to_string(vector.x)+", "+std::to_string(vector.y)+", "+std::to_string(vector.z)+"]";
    return s;
}
std::string quatToSting(glm::quat qua)
{
    std::string s = "["+std::to_string(qua.x)+", "+std::to_string(qua.y)+", "+std::to_string(qua.z)+", "+std::to_string(qua.w)+"]";
    return s;
}
bool CGEngine::Transform::Deserialize(const rapidjson::Value& obj)
{
    return true;
}
bool CGEngine::Transform::Serialize(rapidjson::Writer<rapidjson::StringBuffer> * writer) const
{

    writer->String("Transformation");
    writer->StartObject();

    writer->String("position");
    writer->String(glm::to_string(position).c_str());

    writer->String("rotation");
    writer->String(glm::to_string(rotation).c_str());

    writer->String("scale");
    writer->String(glm::to_string(scale).c_str());

    if(parent!=nullptr) {
        writer->String("parent");
        writer->String((parent->entity->name).c_str());
    }

    writer->String("rootOrder");
    writer->String(std::to_string(rootOrder).c_str());

    if(childCount()!=0) {
        writer->String("children");
        writer->StartArray();
        for (auto &child: children) {
            child.second->entity->Serialize(writer);
        }
        writer->EndArray();
    }

    writer->EndObject();

    return true;
}
