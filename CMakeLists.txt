cmake_minimum_required(VERSION 3.28)
project(launcherClient LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Default to Debug for single-config generators when no build type is set.
if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

include(FetchContent)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)


FetchContent_MakeAvailable(SFML)
find_package(nlohmann_json REQUIRED)

add_executable(main
    src/main.cpp
    src/ConfigParser.cpp
    src/SimpleJson.cpp
    src/Engine.cpp
    src/StateStack.cpp
    src/TopPanel.cpp
    src/gui/GuiCommon.cpp
    src/gui/Label.cpp
    src/gui/Image.cpp
    src/gui/Panel.cpp
    src/gui/Checkbox.cpp
    src/gui/Slider.cpp
    src/gui/List.cpp
    src/gui/TextBox.cpp
    src/gui/Window.cpp
    src/gui/Dialog.cpp
    src/gui/Button.cpp
    src/gui/TextureSelector.cpp
    src/State.cpp
    src/states/GeneralSettingsState.cpp
    src/states/RotationState.cpp
)

target_compile_features(main PRIVATE cxx_std_17)

target_link_libraries(main PRIVATE
    SFML::Graphics
    nlohmann_json::nlohmann_json
    tinyfiledialogs
)

target_include_directories(main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# full debug info
target_compile_options(main PRIVATE
    -O0
    -g
    -fno-omit-frame-pointer
)

add_custom_target(flamegraph
    COMMAND perf record -F 99 -g -- $<TARGET_FILE:main>
    COMMAND perf script > perf.out
    COMMAND ${CMAKE_SOURCE_DIR}/FlameGraph/stackcollapse-perf.pl perf.out > perf.folded
    COMMAND ${CMAKE_SOURCE_DIR}/FlameGraph/flamegraph.pl perf.folded > flamegraph.svg
    COMMAND xdg-open flamegraph.svg
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS main
    COMMENT "hell yeah"
)

add_custom_target(flamegraph-quiet
    COMMAND perf record -F 99 -g -- $<TARGET_FILE:main>
    COMMAND perf script > perf.out
    COMMAND ${CMAKE_SOURCE_DIR}/FlameGraph/stackcollapse-perf.pl perf.out > perf.folded
    COMMAND ${CMAKE_SOURCE_DIR}/FlameGraph/flamegraph.pl perf.folded > flamegraph.svg
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS main
    COMMENT "hell yeah -quiet"
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
