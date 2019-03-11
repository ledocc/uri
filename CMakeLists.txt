#------------------------------------------------------------------------------
# define minimum cmake version
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)


include("${CMAKE_CURRENT_LIST_DIR}/cmake/cmut/cmut.cmake" REQUIRED)


#------------------------------------------------------------------------------
# define project name
#------------------------------------------------------------------------------
cmut__config__print_info()
cmut__project__read_version_file( version "${CMAKE_CURRENT_LIST_DIR}/version.txt" )

project( uri VERSION ${version} )
cmut__config__log_project_begin()

string(TIMESTAMP http_BUILD_TIME "%Y-%m-%d %H:%M:%S UTC" UTC)


#------------------------------------------------------------------------------
# define option
#------------------------------------------------------------------------------

cmut__config__option_build_shared_libs( ON )
option(BUILD_DEPENDENCIES "use conan to install/build dependencies" OFF)
option(URI__FORCE_INCLUDE_CONAN_PATHS_CMAKE "Include \"conan_paths.cmake\" generated in binary directory by used with conan." OFF)


##--------------------------------------------------------------------------------------------------------------------##
# install dependencies
##--------------------------------------------------------------------------------------------------------------------##
if(BUILD_DEPENDENCIES)
#    cmut__lang__set_if_not_defined(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD 14)

    cmut__conan__download_cmake_conan()
    include(${CMAKE_BINARY_DIR}/conan.cmake)
    conan_check(VERSION 1.0.0 REQUIRED)

    if(BUILD_SHARED_LIBS)
        set(CONAN_CMAKE_RUN__OPTIONS OPTIONS "*:shared=True")
    else()
        set(CONAN_CMAKE_RUN__OPTIONS OPTIONS "*:shared=False")
    endif()

    if(DEFINED CMAKE_CXX_STANDARD)
        set(CONAN_CMAKE_RUN__SETTINGS SETTINGS "cppstd=${CMAKE_CXX_STANDARD}")
    endif()


    conan_cmake_run(
        CONANFILE conanfile.py
        BUILD missing
        ${CONAN_CMAKE_RUN__SETTINGS}
        ${CONAN_CMAKE_RUN__OPTIONS}
        )
endif()
if( BUILD_DEPENDENCIES OR CONAN_EXPORTED OR URI__FORCE_INCLUDE_CONAN_PATHS_CMAKE)
    if(CONAN_EXPORTED OR URI__FORCE_INCLUDE_CONAN_PATHS_CMAKE)
        cmut__conan__capture_cxx_standard()
    endif()
    include( "${CMAKE_BINARY_DIR}/conan_paths.cmake" )
endif()


#------------------------------------------------------------------------------
# find dependencies
#------------------------------------------------------------------------------
include("${CMAKE_CURRENT_LIST_DIR}/cmake/dependencies/include_all.cmake")

#include(cmut_print_target_properties)
#cmut_print_target_interface_properties(Boost::boost)


#------------------------------------------------------------------------------
# define build policies
#------------------------------------------------------------------------------

set(CMAKE_DEBUG_POSTFIX "d")

# define CMAKE_*_OUTPUT_DIRECTORY
cmut__build__define_output_dir()

# add option to enable build with all cpu's core when use Visual Studio or nmake
cmut__build__msvc__option_use_mp()

# enable C++14
#cmut__build__enable_cxx_standard(14)

# enable warning
cmut__build__enable_warning(AGGRESSIVE)

# use RUNPATH instead of depreciated RPATH
cmut__build__enable_runpath_link()

cmut__build__set_cxx_visibility(hidden)

if (MSVC)
    add_definitions(-DUNICODE)
endif()

if (MSVC)
    add_definitions(-DUNICODE)
endif()


# add sqoolManager include directory for all target
include_directories(${CMAKE_SOURCE_DIR}/include)


#------------------------------------------------------------------------------
# define subdirectories
#------------------------------------------------------------------------------
add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()
#------------------------------------------------------------------------------
# define uninstall policies
#------------------------------------------------------------------------------
#include( cmut_define_uninstall_target )

cmut__config__log_project_end()
