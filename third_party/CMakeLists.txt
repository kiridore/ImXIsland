include_directories(.)
# curl
set(BUILD_CURL_EXE OFF)
set(BUILD_TESTING OFF)
set(BUILD_EXAMPLES OFF)
set(BUILD_STATIC_LIBS OFF)
set(BUILD_MISC_DOCS OFF)
set(ENABLE_CURL_MANUAL OFF)
add_subdirectory(./curl/)

# glfw
add_subdirectory(glfw)
include_directories(./glfw/include/)

#json
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(./json/)

#SDL2
include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG release-2.30.6
)
message(STATUS "Fetching SDL ...")
FetchContent_MakeAvailable(SDL2)

# imgui
file(GLOB IMGUI_STAR_SOURCE
    "./imgui/imgui*.cpp"
)

set(IMGUI_BACKEND_SOURCE)

list(APPEND IMGUI_BACKEND_SOURCE
    ./imgui/backends/imgui_impl_sdl2.cpp
    ./imgui/backends/imgui_impl_sdlrenderer2.cpp
)

add_library(imgui STATIC
    ${IMGUI_STAR_SOURCE}
    ${IMGUI_BACKEND_SOURCE}
)

target_include_directories(imgui PUBLIC
    ./imgui/backends/
    ./imgui/
    ${SDL2_SOURCE_DIR}/include/
)

target_link_libraries(imgui PUBLIC
    SDL2::SDL2
)
