cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
get_filename_component(ROOT_NAME ${CMAKE_SOURCE_DIR} NAME)
message("Configure project: ${ROOT_NAME}")
project(${ROOT_NAME} VERSION 0.1.0)

option(ENABLE_DOCS "Enable doxygen docs" ON)
option(PRECOMPILED_HEADERS_ENABLED "Enable generate precompile headers" ON)

add_subdirectory(External)
# just for qt
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX "d")
set(CMAKE_RELEASE_POSTFIX "") 
# your thirdparty cmake scripts
set(CMAKE_MODULE_PATH "D:/ThirdParty/cmake" ${CMAKE_MODULE_PATH})

include(CMakeModules/doxygen.cmake)
include(CMakeModules/dependency-graph.cmake)
include(CMakeModules/formatting.cmake)
# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

add_subdirectory(Modules)
add_subdirectory(Apps)
add_subdirectory(Tests)

if(ENABLE_DOCS)
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../Docs)
  build_docs(PROCESS_DOXYFILE TRUE DOXYFILE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile.in)
endif()
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT DemoApp)

if(CLANG_FORMAT_EXE)
  message(STATUS "Found clang format ............ Configuring ..............")
  file(GLOB_RECURSE FFILES ${CMAKE_SOURCE_DIR}/Modules/*.[hc] ${CMAKE_SOURCE_DIR}/Modules/*.[hc]pp ${CMAKE_SOURCE_DIR}/Apps/*.[hc] ${CMAKE_SOURCE_DIR}/Apps/*.[hc]pp)
  clang_format(${PROJECT_NAME}Format ${FFILES})
  set_target_properties(${PROJECT_NAME}Format PROPERTIES FOLDER Tools)
  add_dependencies(${PROJECT_NAME}CommonPrecompiledHeaders ${PROJECT_NAME}Format)
endif()

if(DOT_EXE)
  message(STATUS "Found Graphviz ............ Configuring ..............")
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../Docs/DependencyGraph)
  gen_dep_graph(
    png 
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/../Docs/DependencyGraph
    TARGET_NAME ${PROJECT_NAME}DependencyGraph
  )
  set_target_properties(${PROJECT_NAME}DependencyGraph PROPERTIES FOLDER Tools)
endif()