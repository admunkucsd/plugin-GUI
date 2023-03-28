cmake_minimum_required(VERSION 3.15)

add_library(test_helpers SHARED)

target_compile_features(test_helpers PRIVATE cxx_std_17)

#set(TEST_HELPERS_INCLUDE_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL TEST_HELPERS_INCLUDE_DIRECTORY)

add_dependencies(test_helpers PLUGIN_API)
target_include_directories(test_helpers PRIVATE ${JUCE_DIRECTORY} ${JUCE_DIRECTORY}/modules ${PLUGIN_HEADER_PATH} include)
target_link_libraries(test_helpers PRIVATE PLUGIN_API)


add_subdirectory(Processors)