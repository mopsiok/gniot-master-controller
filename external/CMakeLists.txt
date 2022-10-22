
# TODO conditional include

# exclude pigpio targets unused by the project, since some of them (testing) causes build errors on linux machine
add_subdirectory(pigpio EXCLUDE_FROM_ALL) 

add_library(Unity STATIC
    unity/src/unity.c
)

target_include_directories(Unity PUBLIC
    unity/src
)