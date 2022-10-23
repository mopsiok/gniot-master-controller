
add_executable(master_controller
    main.c
    hw_config.c
    bsp/bsp.c
    utils/log.c
)

# TODO will break future test mocks, to be moved to main cmake?
# TODO most probably TEST/RPI define handled here
target_include_directories(master_controller PUBLIC
    ../external/pigpio
)

target_link_libraries(master_controller PUBLIC 
    pigpio 
    rt
)

set_property(TARGET master_controller PROPERTY C_STANDARD 11)

# TODO not working now, for future research
add_custom_target(bin_conversion
    COMMAND             ${CMAKE_OBJCOPY} -O binary master_controller master_controller.bin
    DEPENDS             master_controller
    WORKING_DIRECTORY   "${CMAKE_BINARY_DIR}"
)