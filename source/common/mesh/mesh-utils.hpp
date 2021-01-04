#ifndef OUR_MESH_UTILS_H
#define OUR_MESH_UTILS_H

#include "mesh.h"

#include <glm/glm.hpp>

namespace CGEngine::mesh_utils {

    //Map for all created meshes
    static std::map<std::string, Mesh*> Meshes;

    Mesh* getMesh(std::string name);

    // Load an ".obj" file into the mesh
    bool loadOBJ(std::string name, const char* filename);

    void Cuboid( std::string name,bool colored_faces = false,
                const glm::vec3& center = {0,0,0},
                const glm::vec3& size = {1,1,1},
                const glm::vec2& texture_offset = {0, 0},
                const glm::vec2& texture_tiling = {1, 1});

    void Sphere(std::string name,
                const glm::ivec2& segments = {32, 16},
                bool colored = false,
                const glm::vec3& center = {0,0,0},
                float radius = 0.5f,
                const glm::vec2& texture_offset = {0, 0},
                const glm::vec2& texture_tiling = {1, 1});

    void Plane(std::string name,
               const glm::ivec2& resolution = {1, 1},
               bool colored = false,
               const glm::vec3& center={0, 0, 0},
               const glm::vec2& size={1, 1},
               const glm::vec2& texture_offset = {0, 0},
               const glm::vec2& texture_tiling = {1, 1});

    void clearMeshes();


}

#endif //OUR_MESH_UTILS_H
