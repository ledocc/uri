from conans import ConanFile, CMake, tools, errors
from conans.client.build.cppstd_flags import cppstd_from_settings, cppstd_default

import os
import platform


def get_package_version():
    version_file_path = os.path.realpath( os.path.join( os.path.dirname( os.path.realpath( __file__ ) ) , "version.txt" ) )
    with open( version_file_path, mode='r' ) as f:
        return f.readline()



class UriConan(ConanFile):
    name = "uri"
    version = tools.load("version.txt")
    author = "David Callu (callu.david at gmail.com)"
    license = "Boost Software License - Version 1.0"
    url = "https://github.com/ledocc/uri"
    description = "uri parser/generator library"
    topics = ("<Put some tag here>", "<here>", "<and here>")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = dict( { "shared":False } )
    exports = "version.txt"

    generators = "cmake_paths"
    scm = {
        "type": "git",
        "url": "https://github.com/ledocc/uri",
        "revision": "auto",
        "submodule": "recursive"
    }
    build_requires = "cmake_installer/3.14.5@conan/stable"
    requires = (("boost/1.70.0@conan/stable"))

    def configure(self):
        cppstd = cppstd_from_settings(self.settings)
        if cppstd == None:
            cppstd = cppstd_default(self.settings.get_safe("compiler"), self.settings.get_safe("compiler.version"))
        if cppstd not in [ None, "98", "gnu98", "11", "gnu11" ]:
            return
        raise errors.ConanInvalidConfiguration("Library uri require C++ 14 or greater.")

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.test(output_on_failure=True)

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.copy("LICENSE_1_0.txt", dst="licenses", ignore_case=True)



    def _configure_cmake(self):
        cmake = CMake(self, set_cmake_flags=True)
        cmake.verbose=True
        if platform.system() != "Windows":
            cmake.definitions["CMAKE_CXX_STANDARD"] = cmake.definitions["CONAN_CMAKE_CXX_STANDARD"]
            cmake.definitions["CMAKE_CXX_EXTENSIONS"] = cmake.definitions["CONAN_CMAKE_CXX_EXTENSIONS"]
        cmake.definitions["CTEST_TEST_TIMEOUT"] = 3000
        cmake.configure()

        return cmake
