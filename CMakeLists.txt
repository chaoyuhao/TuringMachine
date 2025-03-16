project(tmp)
cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(${PROJECT_SOURCE_DIR}/fla-project/lib)

aux_source_directory(${PROJECT_SOURCE_DIR}/fla-project/src CPP_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(fla ${CPP_SRC})

add_custom_command(TARGET fla POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:fla> ${PROJECT_SOURCE_DIR}/fla.exe)