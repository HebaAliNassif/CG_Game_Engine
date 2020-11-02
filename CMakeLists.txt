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
        source/common/application.cpp
        source/common/texture/screenshot.cpp
        )


include_directories(
        source/common
        vendor/glfw/include
        vendor/glad/include
        vendor/glm
        vendor/imgui
        vendor/utils
)

add_executable(Computer_Graphics_Project source/main.cpp ${COMMON_SOURCES} ${VENDOR_SOURCES})
target_link_libraries(Computer_Graphics_Project glfw)