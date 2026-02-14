cmake_minimum_required(VERSION 3.15)

project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------: Dependences
add_subdirectory(ext)

# -----------------------------------------------------------------------------: Targets
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad)
