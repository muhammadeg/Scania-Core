cmake_minimum_required(VERSION 3.12)

project(Data)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 10)

# Source files
set(SOURCE_FILES
    Core/Core.cpp
)

# Create the DLL
add_library(MyDLL SHARED ${SOURCE_FILES})

# Include header files
target_include_directories(MyDLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)

# Set the output directory for the DLL
set_target_properties(MyDLL PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/release
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/release
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/release
)

# Set the toolset version (v100 for Visual Studio 2010)
if(MSVC)
    set_target_properties(MyDLL PROPERTIES
        VS_PLATFORM_TOOLSET "v100"
    )
endif()
