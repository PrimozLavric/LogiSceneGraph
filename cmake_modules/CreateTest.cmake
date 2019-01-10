##############################################
#
# Creat a CTest test from the given name,
# sources, includes and dependencies.
#
# Parameters:
# - TEST_NAME       Test name.
# - SOURCES         List of test sources.
# - INCLUDES        List of test includes.
# - DEPENDENCIES    List of test dependencies.
#
##############################################
macro(create_test TEST_NAME SOURCES INCLUDES DEPENDENCIES)

    add_executable(${TEST_NAME} ${SOURCES})

    target_include_directories(${TEST_NAME} PRIVATE
        "$<BUILD_INTERFACE:${INCLUDES}>"
        $<INSTALL_INTERFACE:include>
    )
    target_link_libraries(${TEST_NAME} ${DEPENDENCIES} ${GTEST_BOTH_LIBRARIES})

    add_test(${TEST_NAME} ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

endmacro()
