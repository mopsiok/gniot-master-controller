if(TARGET_GROUP STREQUAL device)
    add_executable(master_controller)
    set_property(TARGET master_controller PROPERTY C_STANDARD 11)

    target_sources(master_controller PUBLIC
        main.c
        hw_config.c
        bsp/bsp.c
        utils/log.c
        )

    target_link_libraries(master_controller PUBLIC 
        pigpio 
        rt
        )

    add_custom_command(TARGET master_controller POST_BUILD
        COMMAND ${CMAKE_SIZE} "$<TARGET_FILE:master_controller>")
endif()
