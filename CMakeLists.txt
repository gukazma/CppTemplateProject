cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
get_filename_component(ROOT_NAME ${CMAKE_SOURCE_DIR} NAME)
message("Configure project: ${ROOT_NAME}")
project(${ROOT_NAME} VERSION 0.1.0)

option(ENABLE_DOCS "Enable doxygen docs" ON)

add_subdirectory(External)
# just for qt
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(DOXYFILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in" CACHE STRING INTERNAL FORCE)

include(cmake/formatting.cmake)
include(cmake/doxygen.cmake)
include(cmake/dependency-graph.cmake)
# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

set(${PROJECT_NAME}_ROOT_DIR "${CMAKE_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${PROJECT_NAME}_ROOT_DIR/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")
# static library output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${${PROJECT_NAME}_ROOT_DIR}/out/lib)
# dynamic library output dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${${PROJECT_NAME}_ROOT_DIR}/out/lib)
# executalbe dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${${PROJECT_NAME}_ROOT_DIR}/out/bin)
# vendors dir
set(VENDORS_DIR ${CMAKE_SOURCE_DIR}/src/Vendors)

add_subdirectory(src)

add_subdirectory(test)

if(ENABLE_DOCS)
  build_docs(PROCESS_DOXYFILE TRUE DOXYFILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in")
endif()
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})



if(CLANG_FORMAT_EXE)
  message(STATUS "Found clang format ............ Configuring ..............")
  file(GLOB_RECURSE FFILES ${CMAKE_SOURCE_DIR}/src/App/*.[hc] ${CMAKE_SOURCE_DIR}/src/Runtime/*.[hc] ${CMAKE_SOURCE_DIR}/src/App/*.[hc]pp ${CMAKE_SOURCE_DIR}/src/Runtime/*.[hc]pp )
  clang_format(format ${FFILES})
  add_dependencies("${PROJECT_NAME}Runtime" "format")
  set_target_properties(format PROPERTIES FOLDER Tools)
endif()

if(DOT_EXE)
  message(STATUS "Found Graphviz ............ Configuring ..............")
  gen_dep_graph(
    "png" 
    OUTPUT_DIR "${${PROJECT_NAME}_ROOT_DIR}/out"
    TARGET_NAME "dep-graph"
  )

  set_target_properties(dep-graph PROPERTIES FOLDER Tools)
endif()