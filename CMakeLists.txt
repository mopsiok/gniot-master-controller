cmake_minimum_required(VERSION 3.10)

set(TARGET_GROUP release CACHE STRING "Group to build")
if(TARGET_GROUP STREQUAL release)
    message(WARNING "Release build, RPI toolchain")
    set(CMAKE_TOOLCHAIN_FILE toolchain-rpi.cmake)
elseif(TARGET_GROUP STREQUAL test)
    message(WARNING "Test build, regular toolchain")
else()
    message(FATAL_ERROR "Unknown TARGET_GROUP: ${TARGET_GROUP}")
endif()

#TODO test define

project(master_controller LANGUAGES C)

add_subdirectory(src)
add_subdirectory(external)

if(TARGET_GROUP STREQUAL test)
    include(CTest)
    add_subdirectory(test)
endif()