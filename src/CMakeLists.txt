add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./
    ${CMAKE_SOURCE_DIR}/third_party/curl/include
)

target_link_libraries(${PROJECT_NAME} 
    curl
)
