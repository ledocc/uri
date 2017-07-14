

link_libraries(uri)

cmut_add_boost_tests(
    parser_test.cpp
    percent_codec_test.cpp
    uri_codec_test.cpp
    )
