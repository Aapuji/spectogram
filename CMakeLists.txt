# Setup the basic CMake environment
cmake_minimum_required(VERSION 3.20)
set(VCPKG_APPLOCAL_DEPS ON)

project(Spectogram 
    VERSION 1.0.0 
    LANGUAGES CXX
)

# Enforce modern C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the main target (Build as a library)
# Gathering source files explicitly keeps tracking clear
add_library(spectogram_lib STATIC 
    src/audio_capture.cpp
    src/processor.cpp
    src/visualizer.cpp
)

# Bind the header search paths to your library target
target_include_directories(spectogram_lib 
    PUBLIC 
        # Anyone linking to this library can use angle brackets <spectogram/...>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE 
        # Only the .cpp files inside this library can find these headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Get SFML
find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

# target_link_libraries(spectogram_lib PUBLIC 
#     SFML::Graphics 
#     SFML::Window 
#     SFML::System
# )

# Define the executable application entry point
add_executable(spectogram 
    src/main.cpp
)

# Link your application to your core library logic
target_link_libraries(spectogram 
    PRIVATE 
        spectogram_lib
        SFML::Graphics 
        SFML::Window 
        SFML::System
)

# Custom post-build command to copy SFML DLLs when app-local tool fails
add_custom_command(TARGET spectogram POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:spectogram>
        $<TARGET_FILE_DIR:spectogram>
    COMMAND_EXPAND_LISTS
)
