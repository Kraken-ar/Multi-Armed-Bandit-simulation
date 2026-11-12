cmake_minimum_required(VERSION 3.10)

project(MultiArmSim 
        VERSION 1.0 
        LANGUAGES CXX )




message("Start Building")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_BINARY_DIR}/bin
)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/results)

add_executable(${PROJECT_NAME}  src/main.cpp 
                                src/Agent.cpp
                                src/Arm.cpp
                                src/Enviroment.cpp 
                                src/reward/RewardModel.cpp 
                                src/reward/GaussianRewardModel.cpp
                                src/reward/StaticRewardModel.cpp
                                src/history/RewardHistoryTracker.cpp
                                src/history/ArmsEstematedHistoryTracker.cpp
                                src/plotting/LinePlotter.cpp
                                src/config/ConfigReader.cpp
                                src/SimulationBuilder.cpp
                               )


set(RAPIDJSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/rapidjson)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include 
                                                ${RAPIDJSON_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${RAPIDJSON_INCLUDE_DIR})

include(FetchContent)

FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
   
)

FetchContent_MakeAvailable(matplotplusplus)

target_link_libraries(${PROJECT_NAME} PUBLIC Matplot++::matplot)