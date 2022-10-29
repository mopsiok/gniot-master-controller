cmake_policy(SET CMP0076 NEW) #supress warning about absolute paths

if(TARGET_GROUP STREQUAL test)
    add_executable(unit_tests)
    set_property(TARGET unit_tests PROPERTY C_STANDARD 11)

    target_sources(unit_tests PUBLIC
        main.c
        ../src/utils/log.c
        )

    # include(CTest)
    target_link_libraries(unit_tests PUBLIC
        unity
        )

    # add_test(nazwazdupy unit_tests) //TODO is that needed?

    add_custom_command(TARGET unit_tests POST_BUILD
        COMMAND ${CMAKE_SIZE} "$<TARGET_FILE:unit_tests>")
endif()