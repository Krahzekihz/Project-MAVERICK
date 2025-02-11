cmake_minimum_required(VERSION 3.14)  # Adjust this to your required CMake version
project(MAVERICK)

# Find the Qt6 package and required components
find_package(Qt6 REQUIRED COMPONENTS Core Sql Widgets)

# Add your executable
add_executable(MAVERICK main.cpp taskmanager.cpp task.cpp)  # Add your source files here

# Link the Qt libraries to your target
target_link_libraries(MAVERICK PRIVATE Qt6::Core Qt6::Sql Qt6::Widgets)

# Set C++ standard
set_target_properties(MAVERICK PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories (if needed)
target_include_directories(MAVERICK PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# If you have a UI file, you can use the following to handle it
# set(CMAKE_AUTOUIC ON)  # Automatically handle .ui files if you have any