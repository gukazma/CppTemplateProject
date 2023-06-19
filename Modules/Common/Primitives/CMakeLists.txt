set(TARGET_NAME "${PROJECT_NAME}Primitives")

file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE HPP_FILES "*.hpp")
file(GLOB_RECURSE CPP_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${HPP_FILES} ${CPP_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${CPP_FILES} ${HEADER_FILES} ${HPP_FILES})
add_library(${PROJECT_NAME}::Primitives ALIAS ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17)
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER Modules)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

# Link dependencies    
target_link_libraries(${TARGET_NAME} 
    PUBLIC
          )

target_include_directories(
  ${TARGET_NAME} 
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)

set_target_properties(${TARGET_NAME}
    PROPERTIES
        FOLDER Modules/Common
)

if(PRECOMPILED_HEADERS_ENABLED)
    target_precompile_headers(${TARGET_NAME} REUSE_FROM ${PROJECT_NAME}CommonPrecompiledHeaders)
    target_link_libraries(${TARGET_NAME} 
        PUBLIC
            ${PROJECT_NAME}CommonPrecompiledHeaders
          )
endif()

packageProject(
  # the name of the target to export
  NAME ${TARGET_NAME}
  # the version of the target to export
  VERSION ${PROJECT_VERSION}
  # a temporary directory to create the config files
  BINARY_DIR ${PROJECT_BINARY_DIR}
  # location of the target's public headers
  INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include
  # should match the target's INSTALL_INTERFACE include directory
  INCLUDE_DESTINATION include
  # (optional) option to install only header files with matching pattern
  INCLUDE_HEADER_PATTERN "*.h"
  # semicolon separated list of the project's dependencies
  # DEPENDENCIES "fmt 7.1.3;cxxopts 2.2.0"
  # (optional) create a header containing the version info
  # Note: that the path to headers should be lowercase
  # VERSION_HEADER "${PROJECT_NAME}/version.h"
  # (optional) create a export header using GenerateExportHeader module
  # EXPORT_HEADER "${PROJECT_NAME}/export.h"
  # (optional) install your library with a namespace (Note: do NOT add extra '::')
  # NAMESPACE ${PROJECT_NAMESPACE}
  # (optional) define the project's version compatibility, defaults to `AnyNewerVersion`
  # supported values: `AnyNewerVersion|SameMajorVersion|SameMinorVersion|ExactVersion`
  # COMPATIBILITY AnyNewerVersion
  # (optional) option to disable the versioning of install destinations
  DISABLE_VERSION_SUFFIX YES
  # (optional) option to ignore target architecture for package resolution
  # defaults to YES for header only (i.e. INTERFACE) libraries
  # ARCH_INDEPENDENT YES
  # (optional) option to generate CPack variables
  # CPACK YES
)