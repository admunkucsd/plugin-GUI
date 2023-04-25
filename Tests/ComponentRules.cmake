#common options for default plug-ins
unset(PROJECT_FOLDER)
unset(COMPONENT_NAME)
set(INSTALL_GTEST OFF)
get_filename_component(PROJECT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} ABSOLUTE)
get_filename_component(COMPONENT_NAME ${PROJECT_FOLDER} NAME)

include(FetchContent)
FetchContent_Declare(
		googletest
		GIT_REPOSITORY    https://github.com/google/googletest.git
		GIT_TAG           release-1.12.1
)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(
		${COMPONENT_NAME}_tests
)
target_compile_features(${COMPONENT_NAME}_tests PRIVATE cxx_std_17)


add_dependencies(${COMPONENT_NAME}_tests gui_testable_source)
target_compile_definitions(${COMPONENT_NAME}_tests PRIVATE -DTEST_RUNNER)
target_link_libraries(${COMPONENT_NAME}_tests PRIVATE gtest_main gui_testable_source)
target_include_directories(${COMPONENT_NAME}_tests PRIVATE ${JUCE_DIRECTORY} ${JUCE_DIRECTORY}/modules)
add_test(NAME ${COMPONENT_NAME}_tests  COMMAND ${COMPONENT_NAME}_tests)


set_property(TARGET ${COMPONENT_NAME}_tests PROPERTY RUNTIME_OUTPUT_DIRECTORY ${BIN_TESTS_DIR}/${COMPONENT_NAME})

add_custom_command(TARGET ${COMPONENT_NAME}_tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${BIN_TESTS_DIR}/common ${BIN_TESTS_DIR}/${COMPONENT_NAME})

get_target_property(PLUGIN_BASES gui_testable_source SOURCES)
source_group("Plugin Base Classes" FILES ${PLUGIN_BASES})
