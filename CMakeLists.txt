#------------------------------------------------------------------------------
# define minimum cmake version
#------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.11)
cmake_policy(VERSION 3.11)


##--------------------------------------------------------------------------------------------------------------------##
# define CMake module path
##--------------------------------------------------------------------------------------------------------------------##
set(CMUT_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake/cmut")
list(INSERT CMAKE_MODULE_PATH 0
    "${CMAKE_CURRENT_LIST_DIR}/cmake"
    "${CMUT_DIR}"
)

include(cmut)
include(cmut_get_git_info)



##--------------------------------------------------------------------------------------------------------------------##
# define project name/version
##--------------------------------------------------------------------------------------------------------------------##
project(uri)
cmut__config__print_info()
cmut__config__log_project_begin()
cmut__utils__set_project_version_from_file("${CMAKE_CURRENT_LIST_DIR}/version.txt")
cmut__utils__get_build_time(${PROJECT_NAME}_BUILD_TIME)


##--------------------------------------------------------------------------------------------------------------------##
# define build options
##--------------------------------------------------------------------------------------------------------------------##
cmut__config__option_build_shared_libs(ON)
include(CTest) # define BUILD_TESTING
cmut__config__option_ccache(ON)
cmut__config__option_clang_tidy(OFF)
cmut__config__option_cppcheck(OFF)
cmut__config__option_include_what_you_use(OFF)

cmut__config__default_build_type(Release)


#------------------------------------------------------------------------------
# find dependencies
#------------------------------------------------------------------------------
find_package(Threads)

include(cmut_print_target_properties)


set(URI_Boost_VERSION 1.60.0)
find_package(Boost ${URI_Boost_VERSION} COMPONENTS atomic REQUIRED)
#cmut_print_target_interface_properties(Boost::boost)


##--------------------------------------------------------------------------------------------------------------------##
# define build policies
##--------------------------------------------------------------------------------------------------------------------##

set(CMAKE_DEBUG_POSTFIX "d")

# define CMAKE_*_OUTPUT_DIRECTORY
cmut__build__define_output_dir()

cmut__build__enable_color_with_ninja()

# enable C++14
cmut__build__enable_cxx_standard(14)

# enable warning
cmut__build__enable_warning(AGGRESSIVE)

# use RUNPATH instead of depreciated RPATH
cmut__build__enable_runpath_link()

cmut__build__set_cxx_visibility(hidden)

# add option to enable build with all cpu's core when use Visual Studio or nmake
cmut__build__msvc__option_use_mp()

if (MSVC)
    add_definitions(-DUNICODE)
endif()


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


##--------------------------------------------------------------------------------------------------------------------##
# define uninstall policies
##--------------------------------------------------------------------------------------------------------------------##

include(cmut_define_uninstall_target)
#add_subdirectory(cmake/install)


cmut__config__log_project_end()
