
include(cmut_boost_test)

cmut_test__find_boost_test(${URI_Boost_VERSION})

cmut_define_output_dirs(".")

add_subdirectory(uri)
