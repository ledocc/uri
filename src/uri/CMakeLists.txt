set(target uri)

add_library(${target} INTERFACE)

set(${target}_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/${target})

target_include_directories(
    ${target}
    INTERFACE
        "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
#        "$<INSTALL_INTERFACE:include>"
    )

target_link_libraries(
    ${target}
    INTERFACE
        Boost::boost
    )

cmut__install__install_target(${target} INCLUDE_DIRECTORIES ${${target}_INCLUDE_DIR})
