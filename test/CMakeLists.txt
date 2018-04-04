
include(cmut_boost_test)

cmut_test__find_boost_test(${URI_Boost_VERSION})

cmut__build__define_output_dir()

add_subdirectory(uri)
