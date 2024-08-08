add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./
    ${CMAKE_SOURCE_DIR}/third_party/curl/include
    ${CMAKE_SOURCE_DIR}/third_party/json/include
)

target_link_libraries(${PROJECT_NAME} 
    curl
    nlohmann_json::nlohmann_json
)

add_executable(imgui_demo
    imgui_demo.cpp
)

target_include_directories(imgui_demo PUBLIC
    ./
    ${CMAKE_SOURCE_DIR}/third_party/imgui
    ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
)

target_link_libraries(imgui_demo
    imgui
    SDL2::SDL2
)
