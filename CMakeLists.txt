cmake_minimum_required(VERSION 3.16.3)

project(CImg)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options (${PROJECT_NAME} PUBLIC -Ofast)

target_include_directories(${PROJECT_NAME} 
                            PUBLIC OpenCLWrapper/OpenCL/include
                            PUBLIC headers/
                            )

target_link_directories(${PROJECT_NAME} 
                        PUBLIC OpenCLWrapper/OpenCL/lib
)

target_link_libraries(${PROJECT_NAME} OpenCL)
