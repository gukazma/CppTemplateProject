# Generated from rasterwindow.pro.

cmake_minimum_required(VERSION 3.16)

# 设置vvpkg
set(CMAKE_TOOLCHAIN_FILE "D:/codes/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(VCPKG_TARGET_TRIPLET "x64-windows-static")

project(cpp_empty_project LANGUAGES CXX)

# find_package(Qt CONFIG) 查找三方库

add_subdirectory(myproject)
