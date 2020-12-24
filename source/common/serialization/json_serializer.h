#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H
#include <filesystem>
#include <cstdio>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/glm.hpp>
#include <json/json.hpp>
#include <fstream>
#include <unordered_map>
#include <cctype>
#include <string>
#include <transform.h>
#include <../../common/ecs/scene.h>
namespace glm {

    template<length_t L, typename T, qualifier Q>
    void from_json(const nlohmann::json &j, vec<L, T, Q> &v) {
        for (length_t index = 0; index < L; ++index)
            v[index] = j[index].get<T>();
    }

    void from_json(const nlohmann::json &j, glm::quat &v) {
        for (length_t index = 0; index < 4; ++index)
            v[index] = j[index].get<float>();
    }
}

void serializeScene(CGEngine::Scene* sceneEntity, std::filesystem::path scenePath, const std::string& spath, bool pretty) {
    scenePath /= std::filesystem::path(spath.c_str());

}

/*
CGEngine:: Transform * saveTransform(const nlohmann::json& json){

    CGEngine::Transform * node = new CGEngine::Transform (
            json.value<glm::vec3>("position", {0, 0, 0}),
            json.value<glm::quat>("rotation", {0, 0, 0,0}),
            json.value<glm::vec3>("scale", {1, 1, 1})
    );

    if(json.contains("children")){
        for(auto& [name, child]: json["children"].items()){
            //    node->children[name] = loadTransform(child);
        }
    }

    if(json.contains("parent")){
        node->parent = loadTransform(json["parent"]);
    }
    return node;
}
*/

CGEngine:: Transform * loadTransform(const nlohmann::json& json){

    CGEngine::Transform * node = new CGEngine::Transform (
            json.value<glm::vec3>("position", {0, 0, 0}),
            json.value<glm::quat>("rotation", {0, 0, 0,0}),
            json.value<glm::vec3>("scale", {1, 1, 1})
    );

    if(json.contains("children")){
        for(auto& [name, child]: json["children"].items()){
        //    node->children[name] = loadTransform(child);
        }
    }

    if(json.contains("parent")){
        node->parent = loadTransform(json["parent"]);
    }
    return node;
}

CGEngine:: Transform * loadEntity(const nlohmann::json& json) {
    if(json.contains("transform")){
        loadTransform(json["transform"]);
    }
}


#endif //JSON_SERIALIZER_H
