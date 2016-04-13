#------------------------------------------------------------------------------
# define minimum cmake version
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)


#------------------------------------------------------------------------------
# define project name
#------------------------------------------------------------------------------
project(uri VERSION 0.1.0)
string(TIMESTAMP http_BUILD_TIME "%Y-%m-%d %H:%M:%S UTC" UTC)


#------------------------------------------------------------------------------
# define policies
#------------------------------------------------------------------------------


#------------------------------------------------------------------------------
# define CMake Module path
#------------------------------------------------------------------------------
set(
    CMAKE_MODULE_PATH
    ${CMAKE_HOME_DIRECTORY}/cmake
    ${CMAKE_HOME_DIRECTORY}/cmake/cmut
    ${CMAKE_MODULE_PATH}
)

# cmake's module
include(CMakePrintHelpers)


# cmut's module
include( cmut_define_output_dirs )
include( cmut_define_install_dirs )
include( cmut_get_git_info )
include( cmut_install_functions )
include( cmut_message )
include( cmut_qmake_query )
include( cmut_win32_use_mp_option )


#------------------------------------------------------------------------------
# find dependencies
#------------------------------------------------------------------------------
find_package(Threads)

include(cmut_print_target_properties)


set(URI_Boost_VERSION 1.60.0)
find_package(Boost ${URI_Boost_VERSION} COMPONENTS atomic REQUIRED)
cmut_print_target_interface_properties(Boost::boost)


#------------------------------------------------------------------------------
# define build policies
#------------------------------------------------------------------------------

# define CMAKE_*_OUTPUT_DIRECTORY
cmut_define_output_dirs()
# add option to enable build with all cpu's core when use Visual Studio or nmake
cmut_win32_use_mp_option()

# enable C++11
include( cmut_enable_cxx11 )

# enable warning
include( cmut_enable_warning )

# use RUNPATH instead of depreciated RPATH
include( cmut_enable_runpath )


if (MSVC)
    add_definitions(-DUNICODE)
#    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
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
include( cmut_define_uninstall_target )

