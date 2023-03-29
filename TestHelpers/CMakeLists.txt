cmake_minimum_required(VERSION 3.15)

add_library(test_helpers SHARED)

target_compile_features(test_helpers PRIVATE cxx_std_17)

add_dependencies(test_helpers PLUGIN_API)
target_include_directories(test_helpers PRIVATE ${JUCE_DIRECTORY} ${JUCE_DIRECTORY}/modules ${PLUGINS_DIRECTORY}/Headers include)
target_link_libraries(test_helpers PRIVATE PLUGIN_API)


add_subdirectory(Processors)
add_subdirectory(Application)
