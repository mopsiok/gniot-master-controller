if(TARGET_GROUP STREQUAL device)
    # exclude pigpio targets unused by the project, since some of them (testing) causes build errors on linux machine
    add_subdirectory(pigpio EXCLUDE_FROM_ALL)

    target_include_directories(master_controller PUBLIC
        pigpio
        )

elseif(TARGET_GROUP STREQUAL test)
    add_library(unity STATIC
        unity/src/unity.c
    )

    target_include_directories(unity PUBLIC
        unity/src
    )

endif()