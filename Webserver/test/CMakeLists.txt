file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/test/*.cpp")
######################################################################################################################
# DEPENDENCIES
######################################################################################################################

######################################################################################################################
# MAKE TARGETS
######################################################################################################################

##########################################
# "make check-tests"
##########################################
add_custom_target(build-tests COMMAND ${CMAKE_CTEST_COMMAND} --show-only)
add_custom_target(check-tests COMMAND ${CMAKE_CTEST_COMMAND} --verbose)

##########################################
# "make server client ..."
##########################################
foreach (test_source ${TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(test_filename ${test_source} NAME)
    string(REPLACE ".cpp" "" test_name ${test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${test_name} EXCLUDE_FROM_ALL ${test_source})
    add_dependencies(build-tests ${test_name})
    add_dependencies(check-tests ${test_name})

    target_link_libraries(${test_name} pine)#TODO:连接的库要改

	#target_include_directories(${test_name} PUBLIC ${SRC_INCLUDE_DIR} ${TEST_INCLUDE_DIR})

    # Set test target properties and dependencies.
    set_target_properties(${test_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        COMMAND ${test_name}
    )

endforeach(test_source ${TEST_SOURCES})