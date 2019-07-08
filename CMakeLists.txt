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

cmut__utils__get_build_time(${PROJECT_NAME}_BUILD_TIME)


#------------------------------------------------------------------------------
# define option
#------------------------------------------------------------------------------

cmut__config__option_build_shared_libs( ON )
include(CTest) # define BUILD_TESTING
cmut__config__option_ccache(ON)
cmut__config__option_clang_tidy(OFF)
cmut__config__option_cppcheck(OFF)
cmut__config__option_include_what_you_use(OFF)
option(BUILD_DEPENDENCIES "use conan to install/build dependencies" OFF)
option(URI__FORCE_INCLUDE_CONAN_PATHS_CMAKE "Include \"conan_paths.cmake\" generated in binary directory by used with conan." OFF)

cmut__config__default_build_type(Release)



##--------------------------------------------------------------------------------------------------------------------##
# install dependencies
##--------------------------------------------------------------------------------------------------------------------##
include("${CMAKE_CURRENT_LIST_DIR}/cmake/build_dependencies.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/cmake/find_dependencies.cmake")



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



# add include directory for all target
include_directories(${CMAKE_SOURCE_DIR}/include)



#------------------------------------------------------------------------------
# define subdirectories
#------------------------------------------------------------------------------
add_subdirectory(src)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()



##--------------------------------------------------------------------------------------------------------------------##
# define install policies
##--------------------------------------------------------------------------------------------------------------------##

cmut__install__install_config_and_version()
cmut__install__install_config_directory(
    DIRECTORY   "cmake/dependencies/find"
    DESTINATION "dependencies/")

cmut__install__add_install_component_targets(devel runtime)



#------------------------------------------------------------------------------
# define uninstall policies
#------------------------------------------------------------------------------
#include( cmut_define_uninstall_target )

cmut__config__log_project_end()
