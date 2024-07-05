cmake_minimum_required(VERSION 3.30.0)
project(planning)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin) #动态库和exe都指定到bin目录下
#CMAKE_LIBRARY_OUTPUT_DIRECTORY
#CMAKE_ARCHIVE_OUTPUT_DIRECTORY

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
add_library(common
SHARED
${SRC_LIST}
)

target_include_directories(common
PUBLIC
${PROJECT_SOURCE_DIR}/include
)

add_executable(planning_main main.cpp)

target_include_directories(planning_main
PUBLIC
${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(planning_main
PUBLIC
common
)