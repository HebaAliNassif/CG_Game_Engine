#ifndef MESH_H
#define MESH_H
#ifndef OUR_MESH_H
#define OUR_MESH_H

#include <map>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <filesystem>

#include <tinyobj/tiny_obj_loader.h>


#include "common-vertex-types.hpp"
#include "common-vertex-attributes.hpp"

#include <glad/gl.h>

#include "vertex-attributes.h"

#define WHITE   CGEngine::Color(255, 255, 255, 255)
#define GRAY    CGEngine::Color(128, 128, 128, 255)
#define BLACK   CGEngine::Color(  0,   0,   0, 255)
#define RED     CGEngine::Color(255,   0,   0, 255)
#define GREEN   CGEngine::Color(  0, 255,   0, 255)
#define BLUE    CGEngine::Color(  0,   0, 255, 255)
#define MAGENTA CGEngine::Color(255,   0, 255, 255)
#define YELLOW  CGEngine::Color(255, 255,   0, 255)
#define CYAN    CGEngine::Color(  0, 255, 255, 255)


namespace CGEngine {

    // A mesh class to hold the vertex array and its associated buffers (VBOs and EBO)
    class Mesh {
    private:
        GLuint vertex_array = 0;
        GLuint element_buffer = 0;
        std::vector<GLuint> vertex_buffers; // We allow the mesh to contain multiple buffers

        bool use_elements = false; // Whether the mesh should be drawn using glDrawElements or just glDrawArrays
        size_t element_size = 1; // The size of the element data type
        // The element data type, The mode of the primitive assembly step
        GLenum element_type = GL_UNSIGNED_SHORT, primitive_mode = GL_TRIANGLES;
        GLsizei element_count = 0, vertex_count = 0; // How meany elements/vertices are there. Needed by draw()

    public:
        // The underlying OpenGL objects creator
        // This receives a list of functions with the signature void(void).
        // Each function setups up how to access each buffer to send data to the attributes
        // So the number of allocated vertex buffer will be equal the number of passed accessor functions
        void create(const std::vector<std::function<void()>>& accessors, bool has_elements = true){
            vertex_buffers.resize(accessors.size()); // reserve space for the vertex buffers

            // Generate & bind the vertex array to store the buffer access details
            glGenVertexArrays(1, &vertex_array);
            glBindVertexArray(vertex_array);

            if(has_elements) {
                // If this mesh will have elements, generate a buffer for it and
                // bind it such that the vertex array can take it into account while drawing
                glGenBuffers(1, &element_buffer);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
                use_elements = true;
            }

            // Generate the needed vertex buffers
            size_t buffer_count = accessors.size();
            glGenBuffers(buffer_count, vertex_buffers.data());

            // bind each buffer and call its corresponding accessor-setup function such that the vertex array stores these configuration details
            for(size_t buffer_index = 0; buffer_index < buffer_count; ++buffer_index){
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[buffer_index]);
                accessors[buffer_index]();
            }

            glBindVertexArray(0); // Remember to unbind the vertex array such that it stops storing any more configuration
        }

        // Was create called (vertex array is allocated)
        [[nodiscard]] bool isCreated() const { return vertex_array != 0; }
        [[nodiscard]] bool hasElements() const { return element_buffer != 0; }
        [[nodiscard]] bool isUsingElements() const { return use_elements; }
        [[nodiscard]] GLenum getPrimitiveMode() const { return primitive_mode; }
        [[nodiscard]] GLsizei getElementCount() const { return element_count; }
        [[nodiscard]] GLsizei getVertexCount() const { return vertex_count; }

        void setUseElements(bool value){ use_elements = value && (element_buffer != 0); }
        void setElementCount(GLsizei value){ element_count = value; }
        void setVertexCount(GLsizei value){ vertex_count = value; }
        void setPrimitiveMode(GLenum mode){ primitive_mode = mode; }

        // Destroy the OpenGL objects if they were allocated
        void destroy(){
            if(vertex_array != 0) glDeleteVertexArrays(1, &vertex_array);
            vertex_array = 0;
            if(element_buffer != 0) glDeleteBuffers(1, &element_buffer);
            element_buffer = 0;
            glDeleteBuffers(vertex_buffers.size(), vertex_buffers.data());
            vertex_buffers.resize(0);
        }

        Mesh() = default;
        // Destroy the OpenGL objects since we are using the RAII pattern for handling GPU resources
        ~Mesh(){ destroy(); }

        // Set the element data from a vector of elements
        template<typename T>
        void setElementData(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW){
            setElementData(data.data(), data.size(), usage);
        }

        // Set the element data from a raw pointer
        template<typename T>
        void setElementData(T const * data, size_t count, GLenum usage = GL_STATIC_DRAW){
            if(element_buffer == 0) {
                std::cerr << "MESH ERROR: Setting element data before creating element buffer\n";
                return;
            }

            element_size = sizeof(T);
            // Note: elements types are always unsigned
            if constexpr (sizeof(T) == 4) element_type = GL_UNSIGNED_INT;
            else if constexpr (sizeof(T) == 2) element_type = GL_UNSIGNED_SHORT;
            else if constexpr (sizeof(T) == 2) element_type = GL_UNSIGNED_BYTE;
            else static_assert(sizeof(T) != sizeof(T), "Unsupported Element type size");

            element_count = count;
            // Bind the elements buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
            // Send data to the buffer
            // The 2nd parameter is the data size in bytes, the 3rd parameter is a pointer to the data
            // The last parameter is how we plan to use the buffer later, we usually follow the following rules:
            // Use GL_STATIC_DRAW for buffers where we don't plan to modify the data again.
            // Use GL_DYNAMIC_DRAW for buffers where we plan to modify the data but not frequently.
            // Use GL_STREAM_DRAW for buffers where we plan to frequently modify the data (once or even more per frame)
            // This helps the driver optimize where to store the buffer.
            // For example, data with GL_STATIC_DRAW are usually stored on the VIDEO memory which is fast for reading in the GPU but slow for writing from the CPU.
            // while data with GL_STREAM_DRAW are usually stored on a part of the RAM that is accessible by the GPU which is slow for reading in the GPU but fast for writing from the CPU.
            // Note that "usage" is just a hint and you can break these rules but you'll most probably suffer from bad performance.
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_count * element_size, data, usage);
        }

        // read the element data from the GPU. Don't use frequently (for the sake of performance)
        template<typename T>
        void getElementData(std::vector<T>& elements){
            assert(sizeof(T) == element_size);
            GLint size;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);
            glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
            assert((size % sizeof(T)) == 0);
            elements.resize(size / sizeof(T));
            glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size, elements.data());
        }

        // read the element data from the GPU. Don't use frequently (for the sake of performance)
        template<typename T>
        std::vector<T>&& getElementData(){
            std::vector<T> elements;
            getElementData(elements);
            return elements;
        }

        // Set the vertex data to one of the VBOs from a vector
        template<typename T>
        void setVertexData(size_t buffer_index, const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW){
            setVertexData(buffer_index, data.data(), data.size(), usage);
        }

        // Set the vertex data to one of the VBOs from a raw pointer
        template<typename T>
        void setVertexData(size_t buffer_index, T const * data, size_t count, GLenum usage = GL_STATIC_DRAW){
            if(buffer_index >= vertex_buffers.size()) {
                std::cerr << "MESH ERROR: Setting vertex data to an out-of-bound vertex buffer (" << buffer_index << " >= " << vertex_buffers.size() << ")\n";
                return;
            }
            // Bind the vertex buffer
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[buffer_index]);
            // Send data to the buffer
            // The 2nd parameter is the data size in bytes, the 3rd parameter is a pointer to the data
            // The last parameter is how we plan to use the buffer later, we usually follow the following rules:
            // Use GL_STATIC_DRAW for buffers where we don't plan to modify the data again.
            // Use GL_DYNAMIC_DRAW for buffers where we plan to modify the data but not frequently.
            // Use GL_STREAM_DRAW for buffers where we plan to frequently modify the data (once or even more per frame)
            // This helps the driver optimize where to store the buffer.
            // For example, data with GL_STATIC_DRAW are usually stored on the VIDEO memory which is fast for reading in the GPU but slow for writing from the CPU.
            // while data with GL_STREAM_DRAW are usually stored on a part of the RAM that is accessible by the GPU which is slow for reading in the GPU but fast for writing from the CPU.
            // Note that "usage" is just a hint and you can break these rules but you'll most probably suffer from bad performance.
            glBufferData(GL_ARRAY_BUFFER, count*sizeof(T), data, usage);
        }


        // Set vertex data to a part of the buffer from a vector
        template<typename T>
        void setVertexSubData(size_t buffer_index, const std::vector<T>& data, GLintptr offset, GLenum usage = GL_STATIC_DRAW){
            setVertexSubData(buffer_index, data.data(), offset, data.size(), usage);
        }

        // Set vertex data to a part of the buffer from a raw pointer
        template<typename T>
        void setVertexSubData(size_t buffer_index, T const * data, GLintptr offset, size_t count, GLenum usage = GL_STATIC_DRAW){
            if(buffer_index >= vertex_buffers.size()) {
                std::cerr << "MESH ERROR: Setting vertex data to an out-of-bound vertex buffer (" << buffer_index << " >= " << vertex_buffers.size() << ")\n";
                return;
            }
            glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[buffer_index]);
            glBufferSubData(GL_ARRAY_BUFFER, offset, count*sizeof(T), data, usage);
        }

        // read the vertex data from the GPU. Don't use frequently (for the sake of performance)
        template<typename T>
        void getVertexData(size_t buffer_index, std::vector<T>& vertices, GLintptr offset = 0, size_t count = 0){
            if(buffer_index >= vertex_buffers.size()) {
                std::cerr << "MESH ERROR: Requesting vertex data to an out-of-bound vertex buffer (" << buffer_index << " >= " << vertex_buffers.size() << ")\n";
                return;
            }
            GLint size;
            if(count == 0) {
                glBindBuffer(GL_ARRAY_BUFFER, vertex_buffers[buffer_index]);
                glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
                size -= offset;
                assert((size % sizeof(T)) == 0);
                vertices.resize(size / sizeof(T));
            } else {
                size = count * sizeof(T);
                vertices.resize(count);
            }
            glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, vertices.data());
        }

        // read the vertex data from the GPU. Don't use frequently (for the sake of performance)
        template<typename T>
        std::vector<T>&& getVertexData(size_t buffer_index, GLintptr offset = 0, size_t count = 0){
            std::vector<T> vertices;
            getVertexData<>(buffer_index, vertices, offset, count);
            return vertices;
        }

        // Send the mesh data down the pipeline
        // Start and count can be used to only send a contiguous subset of the data
        // if count is 0, it will send all the vertices from start till the end of the vertices
        void draw(GLsizei start = 0, GLsizei count = 0) const {
            if(use_elements) {
                const void *pointer = (void *) (element_size * start);
                if (count == 0) count = element_count - start;
                glBindVertexArray(vertex_array); // First we bind the vertex array since it know how to send the data from the buffers to shader attributes
                glDrawElements(primitive_mode, count, element_type, pointer); // Then we draw
                glBindVertexArray(0); // Then unbind the vertex array
            } else {
                if (count == 0) count = vertex_count - start;
                glBindVertexArray(vertex_array); // First we bind the vertex array since it know how to send the data from the buffers to shader attributes
                glDrawArrays(primitive_mode, start, count); // Then we draw
                glBindVertexArray(0); // Then unbind the vertex array
            }
        }

        //Delete copy constructor and assignment operation
        //This is important for Class that follow the RAII pattern since we destroy the underlying OpenGL object in deconstruction
        //So if we copied the object, one of them can destroy the object(s) while the other still thinks they are valid.
        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;


        //draw sphere
        void Sphere(Mesh& mesh,
                    const glm::ivec2& segments = {32, 16},
                    bool colored = false,
                    const glm::vec3& center = {0,0,0},
                    float radius = 0.5f,
                    const glm::vec2& texture_offset = {0, 0},
                    const glm::vec2& texture_tiling = {1, 1}){

            std::vector<CGEngine::Vertex> vertices;
            std::vector<GLuint> elements;

            // We populate the sphere vertices by looping over its longitude and latitude
            for(int lat = 0; lat <= segments.y; lat++){
                float v = (float)lat / segments.y;
                float pitch = v * glm::pi<float>() - glm::half_pi<float>();
                float cos = glm::cos(pitch), sin = glm::sin(pitch);
                for(int lng = 0; lng <= segments.x; lng++){
                    float u = (float)lng/segments.x;
                    float yaw = u * glm::two_pi<float>();
                    glm::vec3 normal = {cos * glm::cos(yaw), sin, cos * glm::sin(yaw)};
                    glm::vec3 position = radius * normal + center;
                    glm::vec2 tex_coords = texture_tiling * glm::vec2(u, v) + texture_offset;
                    CGEngine::Color color = colored ? CGEngine::Color(127.5f * (normal + 1.0f), 255) : WHITE;
                    vertices.push_back({position, color, tex_coords, normal});
                }
            }

            for(int lat = 1; lat <= segments.y; lat++){
                int start = lat*(segments.x+1);
                for(int lng = 1; lng <= segments.x; lng++){
                    int prev_lng = lng-1;
                    elements.push_back(lng + start);
                    elements.push_back(lng + start - segments.x - 1);
                    elements.push_back(prev_lng + start - segments.x - 1);
                    elements.push_back(prev_lng + start - segments.x - 1);
                    elements.push_back(prev_lng + start);
                    elements.push_back(lng + start);
                }
            }

            // Create and populate the OpenGL objects in the mesh
            if (mesh.isCreated()) mesh.destroy();
            mesh.create({CGEngine::setup_buffer_accessors<Vertex>});
            mesh.setVertexData(0, vertices);
            mesh.setElementData(elements);
        }
        //draw cuboid
        void Cuboid(Mesh& mesh, bool colored_faces = false,
                    const glm::vec3& center = {0,0,0},
                    const glm::vec3& size = {1,1,1},
                    const glm::vec2& texture_offset = {0, 0},
                    const glm::vec2& texture_tiling = {1, 1}){

                // These are just temporary variables that will help us populate the vertex array
                glm::vec3 half_size = size * 0.5f;
                glm::vec3 bounds[] = {center - half_size, center + half_size};
                glm::vec3 corners[] = {
                        {bounds[0].x, bounds[0].y, bounds[0].z},
                        {bounds[0].x, bounds[0].y, bounds[1].z},
                        {bounds[0].x, bounds[1].y, bounds[0].z},
                        {bounds[0].x, bounds[1].y, bounds[1].z},
                        {bounds[1].x, bounds[0].y, bounds[0].z},
                        {bounds[1].x, bounds[0].y, bounds[1].z},
                        {bounds[1].x, bounds[1].y, bounds[0].z},
                        {bounds[1].x, bounds[1].y, bounds[1].z}
                };
                glm::vec2 tex_coords[] = {
                        texture_offset,
                        texture_offset + glm::vec2(0, texture_tiling.y),
                        texture_offset + glm::vec2(texture_tiling.x, 0),
                        texture_offset + texture_tiling
                };
                glm::vec3 normals[3][2] = {
                        {{-1, 0, 0}, {1,0,0}},
                        {{ 0,-1, 0}, {0,1,0}},
                        {{ 0, 0,-1}, {0,0,1}}
                };


                // We populate each face with 4 vertices that define it's corners
                std::vector<Vertex> vertices = {
                        //Upper Face
                        {corners[2], colored_faces ? GREEN : WHITE , tex_coords[0], normals[1][1]},
                        {corners[3], colored_faces ? MAGENTA : WHITE, tex_coords[2], normals[1][1]},
                        {corners[7], colored_faces ? RED : WHITE, tex_coords[3], normals[1][1]},
                        {corners[6], colored_faces ? BLUE : WHITE, tex_coords[1], normals[1][1]},
                        //Lower Face
                        {corners[0], colored_faces ? GREEN : WHITE, tex_coords[0], normals[1][0]},
                        {corners[4], colored_faces ? MAGENTA : WHITE, tex_coords[2], normals[1][0]},
                        {corners[5], colored_faces ? RED : WHITE, tex_coords[3], normals[1][0]},
                        {corners[1], colored_faces ? BLUE : WHITE, tex_coords[1], normals[1][0]},
                        //Right Face
                        {corners[4], colored_faces ? GREEN : WHITE, tex_coords[0], normals[0][1]},
                        {corners[6], colored_faces ? MAGENTA : WHITE, tex_coords[2], normals[0][1]},
                        {corners[7], colored_faces ? RED : WHITE, tex_coords[3], normals[0][1]},
                        {corners[5], colored_faces ? BLUE : WHITE, tex_coords[1], normals[0][1]},
                        //Left Face
                        {corners[0], colored_faces ? GREEN : WHITE, tex_coords[0], normals[0][0]},
                        {corners[1], colored_faces ? MAGENTA : WHITE, tex_coords[2], normals[0][0]},
                        {corners[3], colored_faces ? RED : WHITE, tex_coords[3], normals[0][0]},
                        {corners[2], colored_faces ? BLUE : WHITE, tex_coords[1], normals[0][0]},
                        //Front Face
                        {corners[1], colored_faces ? GREEN : WHITE, tex_coords[0], normals[2][1]},
                        {corners[5], colored_faces ? MAGENTA : WHITE, tex_coords[2], normals[2][1]},
                        {corners[7], colored_faces ? RED : WHITE, tex_coords[3], normals[2][1]},
                        {corners[3], colored_faces ? BLUE : WHITE, tex_coords[1], normals[2][1]},
                        //Back Face
                        {corners[0], colored_faces ? GREEN : WHITE, tex_coords[0], normals[2][0]},
                        {corners[2], colored_faces ? MAGENTA : WHITE, tex_coords[2], normals[2][0]},
                        {corners[6], colored_faces ? RED : WHITE, tex_coords[3], normals[2][0]},
                        {corners[4], colored_faces ? BLUE : WHITE, tex_coords[1], normals[2][0]},
                };
                // Then we define the elements for the 2 triangles that define each face
                std::vector<GLuint> elements = {
                        //Upper Face
                        0, 1, 2, 2, 3, 0,
                        //Lower Face
                        4, 5, 6, 6, 7, 4,
                        //Right Face
                        8, 9, 10, 10, 11, 8,
                        //Left Face
                        12, 13, 14, 14, 15, 12,
                        //Front Face
                        16, 17, 18, 18, 19, 16,
                        //Back Face
                        20, 21, 22, 22, 23, 20,
                };

                // Create and populate the OpenGL objects in the mesh
                if (mesh.isCreated()) mesh.destroy();
                mesh.create({CGEngine::setup_buffer_accessors<Vertex>});
                mesh.setVertexData(0, vertices);
                mesh.setElementData(elements);
            };

    };

}

#endif //OUR_MESH_H

#endif //MESH_H
