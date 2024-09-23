from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("plog/1.1.10")
        self.requires("cxxopts/3.2.0")

    def layout(self):
        cmake_layout(self)