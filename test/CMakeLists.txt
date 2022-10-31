if(TARGET_GROUP STREQUAL test)
    add_executable(unit_tests)
    set_property(TARGET unit_tests PROPERTY C_STANDARD 11)

    target_sources(unit_tests PUBLIC
        main.c
        ../src/utils/log.c
        )

    include(CTest) #let CTest know we're running tests
    target_link_libraries(unit_tests PUBLIC
        unity
        )

    # add_test(nazwazdupy unit_tests) //TODO is that needed?
endif()