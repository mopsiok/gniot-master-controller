cmake_minimum_required(VERSION 3.10)

set(TARGET_GROUP device CACHE STRING "Target to build [device/test]")
set(LOG_LEVEL 3 CACHE STRING "Log level (0/1/2/3 => OFF/ERROR/INFO/DEBUG")

add_compile_definitions(LOG_LEVEL=${LOG_LEVEL})

if(TARGET_GROUP STREQUAL device)
    message(WARNING "Device build, RPI toolchain")
    set(CMAKE_TOOLCHAIN_FILE toolchain-rpi.cmake)
elseif(TARGET_GROUP STREQUAL test)
    message(WARNING "Test build, regular toolchain")
else()
    message(FATAL_ERROR "Unknown TARGET_GROUP: ${TARGET_GROUP}")
endif()

project(master_controller LANGUAGES C)
cmake_policy(SET CMP0076 NEW) #supress warning about absolute paths

add_subdirectory(src)
add_subdirectory(external)

if(TARGET_GROUP STREQUAL test)
    add_subdirectory(test)
endif()