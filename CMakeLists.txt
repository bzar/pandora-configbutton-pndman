cmake_minimum_required(VERSION 2.6)

project(pandora-configbutton-pndman)

include_directories(lib/pndman/src/include lib/pandora-configbutton/src/include)

add_subdirectory(lib)

ADD_DEFINITIONS(-fPIC)
add_library(pandora-configbutton-pndman SHARED src/pndman.c)
add_executable(pndman-sync src/sync.c)
target_link_libraries(pandora-configbutton-pndman pndman)
target_link_libraries(pndman-sync pndman)
