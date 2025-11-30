# TODO: add a uni-library <2025-12-01 07:14, @qiekn> #

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
add_subdirectory(deps/glm)
add_subdirectory(deps/imgui)
add_subdirectory(deps/stb_image)

target_link_libraries(<++> PUBLIC
  glfw
  glad
  glm
  imgui
  stb_image
)
