from conans import ConanFile, CMake, tools, RunEnvironment
import os


class UriConan(ConanFile):
    name = "uri"
    version = tools.load("version.txt").rstrip()
    author = "David Callu (callu.david at gmail.com)"
    license = "Boost Software License - Version 1.0"
    url = "https://github.com/ledocc/uri"
    description = "uri parser/generator library"
    topics = ("uri")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = dict( { "shared":False } )
    
    exports = "version.txt"
    no_copy_source = True

    generators = ("cmake","cmake_paths","virtualrunenv")
    scm = {
        "type": "git",
        "url": "https://github.com/ledocc/uri",
        "revision": "auto",
        "submodule": "recursive"
    }
    requires = "boost/1.73.0@"

    def configure(self):
        tools.check_min_cppstd(self, 14)

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        env_test = {
            "CTEST_TEST_TIMEOUT": "3000",
            "BOOST_TEST_BUILD_INFO": "1",
            "BOOST_TEST_LOG_LEVEL": "message",
            "BOOST_TEST_RANDOM": "1"
        }
        env_build = RunEnvironment(self).vars
        with tools.environment_append(env_build):
            with tools.environment_append(env_test):
                cmake.test(output_on_failure=True)

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
        self.copy("LICENSE_1_0.txt", dst="licenses", ignore_case=True)



    def _configure_cmake(self):
        cmake = CMake(self, set_cmake_flags=True)
        cmake.verbose=True
        cmake.generator="Ninja"

        cmake.definitions["Boost_USE_STATIC_LIBS"] = "FALSE" if self.options["boost"].shared else "TRUE"
        cmake.configure()

        return cmake
