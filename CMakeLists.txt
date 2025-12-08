cmake_minimum_required(VERSION 3.15)

project(main)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# -----------------------------------------------------------------------------: Core
set(CORE_DIR ${PROJECT_SOURCE_DIR}/core)
file(GLOB_RECURSE core_sources CONFIGURE_DEPENDS ${CORE_DIR}/src/*.cc)

add_library(core STATIC ${core_sources}) # cg → computer graphics

target_include_directories(core
 PUBLIC ${CORE_DIR}/include
)

add_subdirectory(core/deps/glfw)
add_subdirectory(core/deps/glad)
add_subdirectory(core/deps/glm)
add_subdirectory(core/deps/imgui)
add_subdirectory(core/deps/spdlog)
add_subdirectory(core/deps/stb_image)
target_link_libraries(core PUBLIC
  glfw
  glad
  glm
  imgui
  spdlog
  stb_image
)

# -----------------------------------------------------------------------------: Sandbox
set(sandbox_dir "${PROJECT_SOURCE_DIR}/sandbox")
set(examples_dir "${PROJECT_SOURCE_DIR}/examples")

file(GLOB_RECURSE sandbox_sources CONFIGURE_DEPENDS
  "${sandbox_dir}/*.cc"
  "${examples_dir}/*.cc"
)

file(GLOB_RECURSE sandbox_headers CONFIGURE_DEPENDS
  "${sandbox_dir}/include/*.hh"
  "${examples_dir}/include/*.cc"
)

message("sources: " ${sandbox_sources})
message("headers: " ${sandbox_headers})

add_executable(sandbox ${sandbox_sources})

target_include_directories(sandbox PRIVATE
  ${sandbox_dir}/include
  ${examples_dir}/include
)

target_link_libraries(sandbox PRIVATE
  core
)
