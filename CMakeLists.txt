cmake_minimum_required(version 3.14)

project(L298N_DRIVER VERSION 1.0.0)

set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/L298N.c
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME}
PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)