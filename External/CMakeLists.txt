list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

# CMake libraries
include(CPM) # keep 1-st
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.6.0")

include(googletest)