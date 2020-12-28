cmake_minimum_required(VERSION 3.0.0)
project(Computer_Graphics_Project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)
add_subdirectory(vendor/glfw)


set(GLAD_SOURCE vendor/glad/src/gl.c)

set(IMGUI_SOURCES
        vendor/imgui/imgui.cpp
        vendor/imgui/imgui_demo.cpp
        vendor/imgui/imgui_draw.cpp
        vendor/imgui/imgui_widgets.cpp
        vendor/imgui/imgui_impl/imgui_impl_glfw.cpp
        vendor/imgui/imgui_impl/imgui_impl_opengl3.cpp
        )


set(VENDOR_SOURCES ${GLAD_SOURCE} ${IMGUI_SOURCES})


set(COMMON_SOURCES
        source/common/application_manager.cpp
        source/common/texture/screenshot.cpp
        source/common/shader/shader.cpp
        source/common/ecs/component.cpp
        source/common/components/transform.cpp
        source/common/ecs/scene.cpp
        source/common/ecs/entity.cpp
        scenes/scene1.cpp
        scenes/scene2.cpp
        source/common/components/mesh_component.cpp
        source/scripts/shape_script.cpp
        source/common/serialization/json_base.cpp
        source/common/mesh/mesh-utils.cpp
        source/common/texture/texture.cpp
        source/common/resource_manager.cpp
        source/common/texture/sampler.cpp
        source/common/texture/sampler_base.cpp
        source/common/material/material.cpp
        )


include_directories(
        source/common
        source/common/components
        source/common/mesh
        source/common/systems
        source/common/ecs
        vendor/glfw/include
        vendor/glad/include
        vendor/glm
        vendor/imgui
        vendor/utils
        vendor/irrklang/include
        assets/shaders/fshaders
        assets/shaders/vshaders
        vendor/irrklang/include
        lib/libs_64
        lib/libs_86
        scenes
        source/scripts
)


if( CMAKE_CL_64)
    configure_file(${CMAKE_SOURCE_DIR}/dlls/dlls_64/ikpMP3.dll ${CMAKE_SOURCE_DIR}/cmake-build-debug COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/dlls/dlls_64/ikpFlac.dll ${CMAKE_SOURCE_DIR}/cmake-build-debug COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/dlls/dlls_64/irrKlang.dll ${CMAKE_SOURCE_DIR}/cmake-build-debug COPYONLY)
    link_directories(${CMAKE_SOURCE_DIR}/lib/libs_64)

else()
    configure_file(${CMAKE_SOURCE_DIR}/dlls/dlls_86/ikpMP3.dll ${CMAKE_SOURCE_DIR}/cmake-build-debug COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/dlls/dlls_86/ikpFlac.dll ${CMAKE_SOURCE_DIR}/cmake-build-debug COPYONLY)
    configure_file(${CMAKE_SOURCE_DIR}/dlls/dlls_86/irrKlang.dll ${CMAKE_SOURCE_DIR}/cmake-build-debug COPYONLY)
    link_directories(${CMAKE_SOURCE_DIR}/lib/libs_86)
endif(CMAKE_CL_64)


add_executable(Computer_Graphics_Project source/manager.cpp ${COMMON_SOURCES} ${VENDOR_SOURCES})
target_link_libraries(Computer_Graphics_Project glfw irrKlang)