cmake_minimum_required(VERSION 3.10)



# set the project name
project(Ising)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtkmm-3.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS} ${PROJECT_SOURCE_DIR})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

# add the executable
add_executable(Ising main.cpp isingWindow.cpp ticker.cpp model.cpp)


# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(Ising ${GTK3_LIBRARIES})
target_compile_options(Ising PRIVATE -rdynamic -W -export-dynamic)
