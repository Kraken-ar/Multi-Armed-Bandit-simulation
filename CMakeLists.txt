cmake_minimum_required(VERSION 3.10)

project(MultiArmSim 
        VERSION 1.0 
        LANGUAGES CXX )




message("Start Building")



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
                               )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


include(FetchContent)

FetchContent_Declare(
    matplotplusplus
    GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus.git
   
)

FetchContent_MakeAvailable(matplotplusplus)

target_link_libraries(${PROJECT_NAME} PUBLIC Matplot++::matplot)