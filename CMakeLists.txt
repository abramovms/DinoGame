cmake_minimum_required(VERSION 3.16)

project(DinoGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    ${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/src/main.cpp
        ${CMAKE_SOURCE_DIR}/src/Classes.cpp
        ${CMAKE_SOURCE_DIR}/src/function.cpp
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

install(TARGETS ${PROJECT_NAME}
        DESTINATION ${CMAKE_SOURCE_DIR}/)