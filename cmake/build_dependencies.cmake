


option(BUILD_DEPENDENCIES "use conan to install/build dependencies" OFF)
option(URI__FORCE_INCLUDE_CONAN_PATHS_CMAKE "Include \"conan_paths.cmake\" generated in binary directory by used with conan." OFF)


if(BUILD_DEPENDENCIES)
    cmut__lang__set_default(CMAKE_CXX_STANDARD 14)

    cmut__conan__download_cmake_conan()
    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_check(VERSION 1.2.0 REQUIRED)

    cmut__cmake_conan__get_shared_option(shared_option)
    cmut__cmake_conan__get_compiler_cppstd_setting(compiler_cppstd_setting)

    conan_cmake_run(
        CONANFILE conanfile.py
        BUILD missing
        ${compiler_cppstd_setting}
        ${shared_option}
        )
endif()

if( BUILD_DEPENDENCIES OR CONAN_EXPORTED OR URI__FORCE_INCLUDE_CONAN_PATHS_CMAKE)
    if(CONAN_EXPORTED OR URI__FORCE_INCLUDE_CONAN_PATHS_CMAKE)
        cmut__conan__capture_cxx_standard()
    endif()
    include( "${CMAKE_BINARY_DIR}/conan_paths.cmake" )
endif()
