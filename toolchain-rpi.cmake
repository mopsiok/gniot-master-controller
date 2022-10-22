set(CMAKE_AR                        arm-linux-gnueabihf-ar)
set(CMAKE_ASM_COMPILER              arm-linux-gnueabihf-gcc)
set(CMAKE_C_COMPILER                arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER              arm-linux-gnueabihf-g++)
set(CMAKE_LINKER                    arm-linux-gnueabihf-ld)
set(CMAKE_OBJCOPY                   arm-linux-gnueabihf-objcopy CACHE INTERNAL "")
set(CMAKE_RANLIB                    arm-linux-gnueabihf-ranlib CACHE INTERNAL "")
set(CMAKE_SIZE                      arm-linux-gnueabihf-size CACHE INTERNAL "")
set(CMAKE_STRIP                     arm-linux-gnueabihf-strip CACHE INTERNAL "")

set(CMAKE_C_FLAGS                   CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS                 "${CMAKE_C_FLAGS}" CACHE INTERNAL "")

set(CMAKE_C_FLAGS_DEBUG             "-Os -g" CACHE INTERNAL "")
set(CMAKE_C_FLAGS_RELEASE           "-Os -DNDEBUG" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_DEBUG           "${CMAKE_C_FLAGS_DEBUG}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS_RELEASE         "${CMAKE_C_FLAGS_RELEASE}" CACHE INTERNAL "")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Without that flag CMake is not able to pass test compilation check
# set(CMAKE_TRY_COMPILE_TARGET_TYPE   STATIC_LIBRARY)