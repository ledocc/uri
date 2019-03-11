set( target uri )

add_library( ${target} INTERFACE )
cmut__project__setup_library( ${target} CXX_FEATURES cxx_std_11 )



set(${target}_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/${target})
set(${target}_INCLUDE_DIR ../..//include/${target})
target_sources(
    ${target}
    INTERFACE
#        ${${target}_INCLUDE_DIR}/detail/tags.hpp

        # ${${target}_INCLUDE_DIR}/fusion/basic_uri.hpp

        # ${${target}_INCLUDE_DIR}/parsers/grammars/uri/grammar.hpp

        # ${${target}_INCLUDE_DIR}/parsers/rules/http/query.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/character.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/fragment.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/host.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/ip.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/path.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/port.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/query.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/scheme.hpp
        # ${${target}_INCLUDE_DIR}/parsers/rules/uri/userinfo.hpp

        # ${${target}_INCLUDE_DIR}/percent/codec.hpp
        # ${${target}_INCLUDE_DIR}/percent/code.hpp

        # ${${target}_INCLUDE_DIR}/phoenix/basic_uri_accessor.hpp

#        ${${target}_INCLUDE_DIR}/schemes/uri/algorithm.hpp
#        ${${target}_INCLUDE_DIR}/schemes/uri/basic_builder.hpp
#        ${${target}_INCLUDE_DIR}/schemes/uri/basic_parser.hpp
#        ${${target}_INCLUDE_DIR}/schemes/uri/ios.hpp
#        ${${target}_INCLUDE_DIR}/schemes/uri/traits.hpp

#        ${${target}_INCLUDE_DIR}/schemes/uri.hpp
#        ${${target}_INCLUDE_DIR}/schemes/http.hpp
#        ${${target}_INCLUDE_DIR}/schemes/mailto.hpp

        ${${target}_RELATIVE_INCLUDE_DIR}/io.hpp
        ${${target}_RELATIVE_INCLUDE_DIR}/uri.hpp
)

target_link_libraries(
    ${target}
    INTERFACE
        Boost::boost
    )

cmut__install__install_target(${target} INCLUDE_DIRECTORIES ${${target}_INCLUDE_DIR})
