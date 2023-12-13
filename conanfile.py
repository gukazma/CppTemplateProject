from conans import ConanFile, tools
import platform


class ModuleConan(ConanFile):
    name = "QtConanExample"
    description = "An example for Qt with Conan"
    settings = "os", "compiler", "build_type", "arch"
    generators = "qt", "cmake", "cmake_find_package_multi", "cmake_paths"
    default_options = {
        "qt:shared": True,
        "qt:qttools": True,
        "openscenegraph:shared": True,
        "boost:shared": True
    }

    def configure(self):
        del self.settings.compiler.cppstd

    def requirements(self):
        self.requires("zlib/1.2.13", override=True)
        self.requires("freetype/2.13.0", override=True)
        self.requires("libpng/1.6.37", override=True)
        self.requires("libjpeg/9e", override=True)
        self.requires("zstd/1.5.5", override=True)
        # self.requires("openscenegraph/3.6.5")
        self.requires("qt/5.15.3")
        self.requires("gtest/1.14.0")
        self.requires("boost/1.83.0")
        
    def imports(self):
        self.copy("*.dll", "./bin", "bin")
        self.copy("osgPlugins-3.6.5", "./bin", "bin")
