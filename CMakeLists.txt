cmake_minimum_required(VERSION 3.10)
project(learn-opengl-v2)

set(CMAKE_CXX_STANDARD 17)

# Find packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Add executable (include glad.c)
add_executable(${PROJECT_NAME} src/main.cpp src/glad.c)

# Include directories for glad and KHR
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link libraries
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)
