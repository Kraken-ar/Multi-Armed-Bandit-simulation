cmake_minimum_required(VERSION 3.10)

project(MultiArmSim 
        VERSION 1.0 
        LANGUAGES CXX )




message("Start Building")

add_executable(${PROJECT_NAME} src/main.cpp )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)