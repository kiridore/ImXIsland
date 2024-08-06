include_directories(.)
# curl
add_subdirectory(./curl/)
set(BUILD_CURL_EXE OFF)
set(BUILD_TESTING OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_STATIC_LIBS OFF)
set(BUILD_MISC_DOCS OFF)
set(ENABLE_CURL_MANUAL OFF)

# glfw
add_subdirectory(glfw)
include_directories(./glfw/include/)

# imgui
file(GLOB IMGUI_STAR_SOURCE
    "./imgui/imgui*.cpp"
)

set(IMGUI_BACKEND_SOURCE)

list(APPEND IMGUI_BACKEND_SOURCE
    ./imgui/backends/imgui_impl_glfw.cpp
    ./imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC
    ${IMGUI_STAR_SOURCE}
    ${IMGUI_BACKEND_SOURCE}
)

target_include_directories(imgui PUBLIC
    ./imgui/backends/
    ./imgui/
)

target_link_libraries(imgui ${OPENGL_LIBRARIES} glfw)

