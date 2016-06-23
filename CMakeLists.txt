cmake_minimum_required(VERSION 2.8.11)

project(qtshot)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(GetGitRevisionDescription)
git_describe(GIT_VERSION --always --dirty)
configure_file(git_version.h.in git_version.h)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc and uic automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 14)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the qtshot executable
set(SOURCES main.cpp dialog.cpp dialog.ui)
add_executable(qtstreamer WIN32 ${SOURCES})

# Use the Widgets module from Qt 5.
target_link_libraries(qtstreamer Qt5::Widgets)
