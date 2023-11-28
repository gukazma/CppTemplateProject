from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class CppTemplateProjectRecipe(ConanFile):
    name = "CppTemplateProject"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake", "cmake_find_package_multi", "cmake_paths"

    exports_sources = "CMakeLists.txt", "Modules/*", "Modules/*"
    def requirements(self):
        self.requires("gtest/1.14.0")
        self.requires("zlib/1.3")
        self.options["zlib"].shared = True
    def configure(self):
        del self.settings.compiler.cppstd
    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["CppTemplateProject"]

    def imports(self):
        self.copy("*.dll", "./bin", "bin")