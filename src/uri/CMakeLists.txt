set(target uri)

add_library(${target} INTERFACE)



set(${target}_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/${target})
target_sources(
    ${target}
    INTERFACE
        ${${target}_INCLUDE_DIR}/detail/tags.hpp
        ${${target}_INCLUDE_DIR}/fusion/adapted_basic_uri.hpp
        ${${target}_INCLUDE_DIR}/parsers/grammars/grammar.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/character.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/fragment.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/host.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/ip.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/path.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/port.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/query.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/scheme.hpp
        ${${target}_INCLUDE_DIR}/parsers/rules/userinfo.hpp
        ${${target}_INCLUDE_DIR}/percent/codec.hpp
        ${${target}_INCLUDE_DIR}/percent/code.hpp
        ${${target}_INCLUDE_DIR}/phoenix/adapted_basic_uri_accessor.hpp
        ${${target}_INCLUDE_DIR}/basic_builder.hpp
        ${${target}_INCLUDE_DIR}/basic_parser.hpp
        ${${target}_INCLUDE_DIR}/basic_uri.hpp
        ${${target}_INCLUDE_DIR}/ios.hpp
        ${${target}_INCLUDE_DIR}/traits.hpp
)

target_link_libraries(
    ${target}
    INTERFACE
        Boost::boost
    )

include(cmut_target_compile_option_cxx_version)
cmut_target_compile_option_cxx_version(${target} INTERFACE 14)
