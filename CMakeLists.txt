cmake_minimum_required( VERSION 3.7.0 )
# Set the project name and version
project(main)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Define a variable with syntax: set(<variable> <value>)
# To use the defined variable: ${variable}
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# Generate a list of files with syntax: file(GLOB <variable> <files>)
# Specify the sources of the project with ${SRC_DIR}
file(GLOB SOURCES "${SRC_DIR}/main.c")
# Add the executable with the sources in ${SOURCES}
add_executable(${PROJECT_NAME} ${SOURCES})
# Find installed packages with syntax: find_package(<PackageName>)
find_package( SDL2 REQUIRED )
# If the package is found, serveral variables associated to the
# library are created: ${SDL2_FOUND} if SDL2 is found in the system
# ${SDL2_INCLUDE_DIRS} contains the path of SDL2 include folder
# ${SDL2_LIBRARIES} contains the path of SDL2 lib
if( ${SDL2_FOUND})
    message(STATUS "Found SDL2")
    # Include directories to build the project
    include_directories(${SDL2_INCLUDE_DIRS})
    # Specify libraries for linking to the project
    target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})
else()
    message(STATUS "Could not locate SDL2")
endif()